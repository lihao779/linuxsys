#pragma once
#include <iostream>
using namespace std;

template<class T>
struct AVLTreeNode
{
    AVLTreeNode(const T& x)
        :left(nullptr)
         ,right(nullptr)
         ,parent(nullptr)
         ,date(x)
         ,bf(0)
    {}

    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;
    AVLTreeNode<T>* parent;
    T date;
    int bf;
};

template<class T>
class AVLTree
{
    typedef AVLTreeNode<T> Node;
    public:
        AVLTree()
            :_root(nullptr)
        {}
        ~AVLTree()
        {}

        bool Insert(const T& date)
        {
            if(_root == nullptr)
            {
                _root = new Node(date);
                return true;
            }

            //找位置
            //插入节点
            Node* cur = _root;
            Node* parent = nullptr;
            while(cur)
            {
                parent = cur;
                if(cur->date > date)
                    cur = cur->left;
                else if(cur->date < date)
                    cur = cur->right;
                else
                    return false;
            }
            //插入新节点
            cur = new Node(date);
            if(date < parent->date)
                parent->left = cur;
            else
                parent->right = cur;
            cur->parent = parent;
            
            //更新双亲平衡因子
            while(parent) //------>parent不为空cur不为空
            {
                if(parent->left == cur)
                    parent->bf--;
                else
                    parent->bf++;

                if(parent->bf == 0)
                    return true;
                else if(parent->bf == 1 || parent->bf == -1)
                {
                   cur = cur->parent;
                   parent = cur->parent;
                }
                else
                {
                    //平衡因子是2 || -2
                    if(parent->bf == 2) // 平衡因子为2表明右子树高 -->最终都得左单旋
                    {
                        if(cur->bf == 1) //平衡因子在2的情况下cur的平衡因子是1表明插在较高右子树的外侧 -->左单旋
                        {
                            RotatoLeft(parent);
                        }
                        else
                        {
                            RotateRL(parent);
                        }
                    }
                    else                // 平衡因子是-2表明左子树高  -->最终都得右单旋
                    {
                        if(cur->bf == -1) //平衡因子在-2的情况下 cur的平衡因子是-1表明插入在较高左子树的外侧 -->右单旋
                        {
                            RotatoRight(parent);
                        }
                        else
                        {
                            RotateLR(parent);
                        }
                    }
                    break;
                }
            }  

            return true;
        }
    
        void InOrder()
        {
            _InOrder(_root);
        }
        bool IsBalanceTree()
        {
            return _IsBalanceTree(_root);
        }

    private:
        //----------------------------
        int _Height(Node* root)
        {
            if(root == nullptr)
                return 0;
            int left = _Height(root->left);
            int right = _Height(root->right);
            return left > right ? left + 1 : right + 1;
        }
        bool _IsBalanceTree(Node* root)
        {
            if(root == nullptr)
                return true;
            int leftHight = _Height(root->left);
            int rightHeight = _Height(root->right);

            if((abs(root->bf)<=1) && (rightHeight-leftHight == root->bf))
            {
                if(_IsBalanceTree(root->left) && _IsBalanceTree(root->right))
                    return true;
            }
            return false; 

        }
        //----------------------------
        void _InOrder(Node* root)
        {
            if(root)
            {
                _InOrder(root->left);
                cout<<root->date<<" ";
                _InOrder(root->right);
            }
        }

        void RotatoLeft(Node* parent)
        {
            Node* grandfather = parent->parent;
            Node* subR = parent->right;
            Node* subRL = subR->left;

            parent->right = subRL;
            if(subRL)
                subRL->parent = parent;
            subR->left = parent;
            parent->parent = subR;
            subR->parent = grandfather; 
            if(grandfather == nullptr)
                _root = subR;
            else
            {
                if(grandfather->left == parent)
                    grandfather->left = subR;
                else
                    grandfather->right = subR;
            }
            subR->bf = parent->bf =0;

        }
        void RotatoRight(Node* parent)
        {
            Node* grandfather = parent->parent;
            Node* subL = parent->left;
            Node* subLR = subL->right;

            parent->left = subLR;
            if(subLR)
                subLR->parent = parent;
            subL->right = parent;
            parent->parent = subL;
            subL->parent = grandfather;
            if(grandfather == nullptr)
                _root = subL;
            else
            {
                if(parent == grandfather->left)
                    grandfather->left = subL;
                else
                    grandfather->right = subL;
            }
            subL->bf = parent->bf = 0;
        }

        void RotateRL(Node* parent)
        {
            Node* subR = parent->right;
            Node* subRL = subR->left;
            int bf = subRL->bf;
            RotatoRight(parent->right);
            RotatoLeft(parent);
            
            if(bf == 1)
            {
                parent->bf = -1;
            }
            else if(bf == -1)
            {
                subR->bf = 1;
            }
            //else--->bf == 0 不需要处理
        }

        void RotateLR(Node* parent)
        {
            Node* subL = parent->left;
            Node* subLR = subL->right;
            int bf = subLR->bf;
            RotatoLeft(parent->left);
            RotatoRight(parent);
            if(bf == 1)
            {
                subL->bf = -1;
            }
            else if(bf == -1)
            {
                parent->bf = 1;
            }

            //else--->bf == 0 不需要处理
            
        }
        private:
        Node* _root;
        
};



void TestAVLTree1()
{
    int array[] = {16,3,7,11,9,26,18,14,15};

    AVLTree<int> t;
    
    for(auto e:array)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout<<endl;
    if(t.IsBalanceTree())
        cout<<"the tree is blancetree"<<endl;
    else
        cout<<"the tree not is blancetree"<<endl;
        
}
void TestAVLTree2()
{
    int array[] = {4,2,6,1,3,5,15,7,16,14};

    AVLTree<int> t;
    
    for(auto e:array)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout<<endl;
    if(t.IsBalanceTree())
        cout<<"the tree is blancetree"<<endl;
    else
        cout<<"the tree not is blancetree"<<endl;
}
