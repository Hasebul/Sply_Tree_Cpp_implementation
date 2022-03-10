#include<bits/stdc++.h>
using namespace std;


class Node
{
public:
    int value;
    Node *parent;
    Node *left;
    Node *right;
    Node()
    {
        value=0;
        parent=0;
        left=0;
        right=0;
    }
    Node(int key,Node *P)
    {
        value=key;
        parent=P;
        left=0;
        right=0;
    }
};


class SplayTree
{
    Node* root;
public:
    SplayTree()
    {
        root=0;
    }
    void leftRotate(Node* targetParent)
    {
        Node *target=targetParent->right;
        targetParent->right=target->left;
        if(target->left!= 0)
            target->left->parent=targetParent;
        if(targetParent->parent ==0)
            root=target;
        else if(targetParent->parent->left== targetParent)
            targetParent->parent->left=target;
        else
            targetParent->parent->right=target;
        target->parent=targetParent->parent;
        target->left=targetParent;
        targetParent->parent=target;

    }

    void rightRotate(Node * targetParent)
    {
        Node *target=targetParent->left;
        targetParent->left=target->right;
        if(target->right !=0)
            target->right->parent=targetParent;
        if(targetParent->parent==0)
            root=target;
        else if(targetParent->parent->left == targetParent)
            targetParent->parent->left=target;
        else
            targetParent->parent->right=target;
        target->parent=targetParent->parent;
        target->right=targetParent;
        targetParent->parent=target;
    }

    void splay(Node *target)
    {
        while(target->parent)
        {
            if(target->parent->parent==0)///zig
            {
                if(target==target->parent->left)
                    rightRotate(target->parent);
                else
                    leftRotate(target->parent);
            }
            else
            {
                if(target->parent->left== target && target->parent->parent->left==target->parent)
                {
                    rightRotate(target->parent->parent);
                    rightRotate(target->parent);
                }
                else if(target->parent->right==target && target->parent->parent->right==target->parent)
                {
                    leftRotate(target->parent->parent);
                    leftRotate(target->parent);
                }
                else if(target->parent->left==target && target->parent->parent->right==target->parent)
                {
                    rightRotate(target->parent);
                    leftRotate(target->parent);
                }
                else if(target->parent->right==target && target->parent->parent->left==target->parent)
                {
                    leftRotate(target->parent);
                    rightRotate(target->parent);
                }


            }
        }
    }

    Node* searchNode(int key)
    {
        if(root==0)
            return 0;
        if(root->value==key)
        {
            cout<<root->value<<" is found "<<endl;
            return root;
        }
        Node *temp=root;
        Node *previous;
        while(temp)
        {
            previous=temp;
            if(temp->value==key) //found
            {
                cout<<temp->value<<" is found "<<endl;
                splay(temp);
                return root;
            }
            else if(temp->value< key)
                temp=temp->right;
            else
                temp=temp->left;
        }
        cout<<key<<" is not found "<<endl;
        splay(previous);

        return 0;
    }

    Node* maximum(Node * temp)
    {
        while(temp->right!=0)
            temp=temp->right;
        return temp;
    }

    Node * minimum(Node *temp)
    {
        while(temp->left!=0)
            temp=temp->left;
        return temp;
    }


    Node* join(Node *L,Node *R)///L and R both are two different tree
    {
        if(L==0)
        {
            root=R;
            return R;
        }
        Node* maxNode=maximum(L);
        splay(maxNode);
        root=maxNode;
        maxNode->right=R;
        if(R!=0)
            R->parent=maxNode;
        return maxNode;
    }

    void deleteNode(int key)
    {
        Node *temp=searchNode(key);
        if(temp==0)
            return;
        Node* leftChild=temp->left;
        Node * rightChild=temp->right;
        temp->left=0;
        temp->right=0;
        if(leftChild!=0)
            leftChild->parent=0;
        if(rightChild!=0)
            rightChild->parent=0;
        root=0;
        delete temp;
        join(leftChild,rightChild);
        return;
    }

    void insertNode(int key)
    {

        Node *temp=root;
        Node *previous=0;

        while(temp)
        {
            previous=temp;
            if(temp->value<key)
                temp=temp->right;
            else if(temp->value>=key)
                temp=temp->left;

        }
        temp=new Node(key,previous);
        if(previous==0)
            root=temp;
        else if(previous->value<key)
            previous->right=temp;
        else if(previous->value>=key)
            previous->left=temp;
        splay(temp);
        return ;

    }


    //---------------------------------------Print_Node_Value--------------------------------------------------------------------


    void print(vector<Node*> nodes,int level,int maxlevel)
    {
        if(nodes.empty() || isAllElement0(nodes))
            return;
        int floor=maxlevel-level;
        int endgelines=pow(2,max(floor-1,0));
        //int endgelines=2*max(floor-1,0);
        int firstSpaces=pow(2,floor)-1;
        int betweenSpaces=pow(2,floor+1)-1;
        printWhiteSpace(firstSpaces);
        vector<Node *> newNodes;
        for(int i=0; i<nodes.size(); i++)
        {
            Node * newNode=nodes[i];
            if(newNode!=0)
            {
                cout<<newNode->value;
                newNodes.push_back(newNode->left);
                newNodes.push_back(newNode->right);
            }
            else
            {
                newNodes.push_back(0);
                newNodes.push_back(0);
                cout<<" ";
            }
            printWhiteSpace(betweenSpaces);
        }

        cout<<"\n";


        for (int i = 1; i <= endgelines; i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                printWhiteSpace(firstSpaces - i);
                if (nodes[j] == 0)
                {
                    printWhiteSpace(endgelines + endgelines + i + 1);
                    continue;
                }

                if (nodes[j]->left != 0)
                    cout<<"/";
                else
                    printWhiteSpace(1);

                printWhiteSpace(i + i - 1);

                if (nodes[j]->right != 0)
                    cout<<"\\";
                else
                    printWhiteSpace(1);

                printWhiteSpace(endgelines + endgelines - i);
            }

            cout<<"\n";
        }

        print(newNodes,level+1,maxlevel);


    }

    int maxLevel(Node *temp)
    {
        if(temp==0)
            return 0;
        return max(maxLevel(temp->left),maxLevel(temp->right))+1;
    }
    bool isAllElement0(vector<Node*> nodes)
    {
        for(int i=0; i<nodes.size(); i++)
        {
            if(nodes[i]!=0)
                return false;
        }
        return true;
    }
    void printWhiteSpace(int con)
    {
        for(int i=0; i<con; i++)
            cout<<" ";

    }

    Node* getRoot()
    {
        return root;
    }

};


int main()
{
    SplayTree st;
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print 5. exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            cin>>item;
            st.insertNode(item);

        }
        else if(ch==2)
        {
            int item;
            cin>>item;
            st.deleteNode(item);


        }
        else if(ch==3)
        {
            int item;
            cin>>item;
            st.searchNode(item);

        }
        else if(ch==4)
        {
            vector<Node*> nodes;
            nodes.push_back(st.getRoot());
            int maxlevel=st.maxLevel(st.getRoot());
            st.print(nodes,1,maxlevel);
        }

        else if(ch==5)
        {
            break;
        }

    }


}







