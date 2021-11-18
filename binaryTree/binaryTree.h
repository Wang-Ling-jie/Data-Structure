#ifndef binaryTree_h
#define binaryTree_h

#include <iostream>
#include "linkStack.h"
#include "linkQueue.h"

using namespace std;

template <class elemtype>
class  binaryTree;

template <class elemtype>
class Node{
    friend class binaryTree<elemtype>;
    private:
        elemtype data;
        Node *left,*right;
        int leftFlag;//用于标识是否线索，0时left为左孩子结点，1时为前驱线索
        int rightFlag;//用于标识是否线索，0时right为右孩子结点，1时为后继线索
    public:
        Node(){left=NULL;right=NULL;leftFlag=0;rightFlag=0;}
        Node(const elemtype &x,Node*L=NULL,Node*R=NULL){
            data=x;
            left=L;right=R;
            leftFlag=0;rightFlag=0;
        }
};

template <class elemtype>
class binaryTree{
    private:
        Node<elemtype> *root;
        
        Node<elemtype>*find(const elemtype&x,Node<elemtype>*t)const;
        int Size(Node<elemtype>*t)const;         //求以t为根的二叉树的节点个数
        int Height(Node<elemtype>*t)const;       //求以t为根的二叉树的高度
        void DelTree(Node<elemtype>*&t);          //删除以t为根的二叉树
        //递归遍历工具函数
        void PreOrder(Node<elemtype>*t)const; 
        void InOrder(Node<elemtype>*t)const; 
        void PostOrder(Node<elemtype>*t)const;
    public:
        binaryTree(){root=NULL;}
        binaryTree(const elemtype &x){root=new Node<elemtype>(x);}
        ~binaryTree();
        bool isEmpty();
        void createTree(const elemtype&flag);
        Node <elemtype>*getRoot(){return root;}
        elemtype Root(const elemtype&flag)const;

        int Size()const;                          //求二叉树的结点个数
        int Height()const;                        //求二叉树的高度
        void DelTree();                      //删除二叉树

        void LevelOrder()const;                   //层次遍历
        void PreOrder()const;                     //递归前序遍历
        void InOrder()const;                      //递归中序遍历
        void PostOrder()const;                    //递归后序遍历
        void preOrder()const;                     //非递归前序遍历
        void inOrder()const;                      //非递归中序遍历
        void postOrder()const;                    //非递归后序遍历
        void midOrder()const;                     //非递归中序遍历另一种实现

        elemtype lchild(const elemtype &x,const elemtype &flag)const;
        elemtype rchild(const elemtype &x,const elemtype &flag)const;
        void delLeft(const elemtype &x);
        void delRight(const elemtype &x);

        Node<elemtype>*buildTree(elemtype pre[],int pl,int pr,elemtype mid[],int ml,int mr);
        
        Node<elemtype>* ThreadMid();
        void ThreadMidVisit(Node<elemtype>*first)const;
        void ThreadMidPreVisit()const;
};  

template <class elemtype>
Node <elemtype>* binaryTree<elemtype>::find(const elemtype &x,Node<elemtype>*t)const{
    Node<elemtype>*tmp;
    if(t==NULL) return NULL;
    if(t->data==x)
        return t;
    if(tmp=find(x,t->left)) return tmp;
    else return find(x,t->right);
}

template <class elemtype>
int binaryTree<elemtype>::Size(Node<elemtype>*t)const{
    if(t==NULL) return 0;
    return 1+Size(t->left)+Size(t->right);
}

template <class elemtype>
int binaryTree<elemtype>::Height(Node<elemtype>*t)const{
    if(t==NULL) return 0;
    return(1+max(Height(t->left),Height(t->right)));
}

template <class elemtype>
void binaryTree<elemtype>::DelTree(Node<elemtype>*&t){
    if(t==NULL) return;
    DelTree(t->left);
    DelTree(t->right);
    delete t;
    t=NULL;
}

template <class elemtype>
void binaryTree<elemtype>::PreOrder(Node<elemtype>*t)const{
    if(t==NULL) return;
    cout<<t->data<<" ";
    PreOrder(t->left);
    PreOrder(t->right);
}

template <class elemtype>
void binaryTree<elemtype>::InOrder(Node<elemtype>*t)const{
    if(t==NULL) return;
    InOrder(t->left);
    cout<<t->data<<" ";
    InOrder(t->right);
}

template<class elemtype>
void binaryTree<elemtype>::PostOrder(Node<elemtype>*t)const{
    if(t==NULL) return;
    PostOrder(t->left);
    PostOrder(t->right);
    cout<<t->data<<" ";
}

template <class elemtype>
binaryTree<elemtype>::~binaryTree(){
    DelTree(root);
}

template <class elemtype>
bool binaryTree<elemtype>::isEmpty(){
    return (root==NULL);
}

template <class elemtype>
void binaryTree<elemtype>::createTree(const elemtype &flag){
    linkQueue<Node<elemtype>*>que;
    elemtype r,el,er;
    Node<elemtype>*p,*pl,*pr;
    cout<<"Please input the root,using "<<flag<<" as empty:";
    cin>>r;
    if(r==flag) {root=NULL;return;}
    root=p=new Node<elemtype>(r);
    que.enQueue(p);
    while(!que.isEmpty()){
        p=que.deQueue();
        cout<<"Please input the left and right child of "<<p->data<<" ,using "<<flag<<" as no child: ";
        cin>>el>>er;
        if(el!=flag){   //该结点有左孩子
            pl=new Node<elemtype>(el);
            p->left=pl;
            que.enQueue(pl);
        }
        if(er!=flag){
            pr=new Node<elemtype>(er);
            p->right=pr;
            que.enQueue(pr);
        }
    }
}

template <class elemtype>
elemtype binaryTree<elemtype>::Root(const elemtype& flag)const{
    if(root==NULL)  return flag;
    return root->data;
}

template <class elemtype>
int binaryTree<elemtype>::Size()const{
    return Size(root);
}

template <class elemtype>
int binaryTree<elemtype>::Height()const{
    return Height(root);
}

template <class elemtype>
void binaryTree<elemtype>::DelTree(){
    DelTree(root);
}

template <class elemtype>
void binaryTree<elemtype>::LevelOrder()const{
    linkQueue<Node<elemtype>*>que;
    if(!root) return;
    que.enQueue(root);
    Node<elemtype>*p;
    cout<<"Level Order traverse: ";
    while(!que.isEmpty()){
        p=que.deQueue();
        cout<<p->data<<" ";
        if(p->left)
            que.enQueue(p->left);
        if(p->right)
            que.enQueue(p->right);
    }
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::PreOrder()const{
    cout<<"PreOrder traverse: ";
    PreOrder(root);
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::InOrder()const{
    cout<<"InOrder traverse: ";
    InOrder(root);
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::PostOrder()const{
    cout<<"PostOrder traverse: ";
    PostOrder(root);
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::preOrder()const{
    linkStack<Node<elemtype>*>sta;
    if(root==NULL) return;
    Node<elemtype>*p;
    sta.push(root);
    cout<<"preOrder traverse: ";
    while(!sta.isEmpty()){
        p=sta.pop();
        cout<<p->data<<" ";
        if(p->right) sta.push(p->right);
        if(p->left) sta.push(p->left);
    }
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::inOrder()const{
    linkStack<Node<elemtype>*> sta;
    Node<elemtype>*p=root;
    if(!root) return;
    cout<<"inOrder traverse:"<<" ";

    sta.push(root);
    while(p->left){
        sta.push(p->left);
        p=p->left;
    }
    while(!sta.isEmpty()){
        p=sta.pop();
        cout<<p->data<<" ";
        if(p->right){
            p=p->right;
            sta.push(p);
            while(p->left){
                sta.push(p->left);
                p=p->left;
            }
        }
    }
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::midOrder()const{
    if(!root) return;
    cout<<"midOrder traverse: ";
    linkStack<Node<elemtype>*>s1;
    linkStack<int> s2;
    int flag;
    const int zero=0,one=1;
    Node<elemtype>*p;
    s1.push(root);
    s2.push(zero);

    while(!s1.isEmpty()) {
        flag=s2.pop();
        p=s1.top();
        if(flag==0){
            s2.push(one);
            if(p->left){//有左子压左子
                s1.push(p->left);
                s2.push(zero);
            }
        }
        else if(flag==1){
            p=s1.pop();
            cout<<p->data<<" ";
            if(p->right){//有右子压右子
                s1.push(p->right);
                s2.push(zero);
            }
        }
    }
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::postOrder()const{
    if(!root) return;
    cout<<"postOrder traverse: ";
    linkStack<Node<elemtype>*>s1;
    linkStack<int>s2;
    int flag;
    const int zero=0,one=1,two=2;
    Node<elemtype>*p;
    s1.push(root);
    s2.push(zero);
    while(!s1.isEmpty()){
        flag=s2.pop();
        p=s1.top();
        switch (flag){
            case 0:
                s2.push(one);
                if(p->left){
                    s1.push(p->left);
                    s2.push(0);
                }
                break;
            case 1:
                s2.push(two);
                if(p->right){
                    s1.push(p->right);
                    s2.push(0);
                }
                break;
            case 2:
                p=s1.pop();
                cout<<p->data<<" ";
                break;
        }
    }
    cout<<endl;
}

template <class elemtype>
elemtype binaryTree<elemtype>::lchild(const elemtype &x,const elemtype &flag)const{
    Node<elemtype>*p=find(x,root);
    if(!p||!p->left) return flag;
    return p->left;
}

template <class elemtype>
elemtype binaryTree<elemtype>::rchild(const elemtype &x,const elemtype &flag)const{
    Node<elemtype>*p=find(x,root);
    if(!p||!p->right) return flag;
    return p->right;
}

template <class elemtype>
void binaryTree<elemtype>::delLeft(const elemtype &x){
    Node<elemtype>*p=find(x,root);
    if(!p||!p->left) return;
    DelTree(p->left);
}

template <class elemtype>
void binaryTree<elemtype>::delRight(const elemtype &x){
    Node<elemtype>*p=find(x,root);
    if(!p||!p->right) return;
    DelTree(p->right);
}

template <class elemtype>
Node<elemtype>* binaryTree<elemtype>::buildTree(elemtype pre[],int pl,int pr,elemtype mid[],int ml,int mr){
    int pos,lpl,lpr,rpl,rpr,lml,lmr,rml,rmr,num;
    Node<elemtype>*p,*leftRoot,*rightRoot;

    if(pl>pr||ml>mr)  return NULL;//递归出口
    p=new Node<elemtype>(pre[pl]);
    if(!root)   root=p;

    //找根在中序中的位置和左子树中的结点个数
    for(pos=ml;pos<mr;++pos){
        if(mid[pos]==pre[pl]) break;
    }//pos为子树根在中序遍历中的下标
    num=pos-ml;//子树根的左子树中结点的个数

    //找左子树的前序、中序遍历的下标范围
    lpl=pl+1;
    lpr=pl+num;
    lml=ml;
    lmr=pos-1;

    //找右子树的前序、中序遍历的下标范围
    rpl=pl+num+1;
    rpr=pr;
    rml=pos+1;
    rmr=mr;

    leftRoot=buildTree(pre,lpl,lpr,mid,lml,lmr);
    rightRoot=buildTree(pre,rpl,rpr,mid,rml,rmr);

    p->left=leftRoot;
    p->right=rightRoot;
    return p;
}

template <class elemtype>
Node<elemtype>*binaryTree<elemtype>::ThreadMid(){
    if(!root) return NULL;

    linkStack<Node<elemtype>*> s1;
    linkStack<int> s2;
    Node<elemtype>*first=NULL;
    Node<elemtype>*p=NULL,*pre=NULL;
    int flag;
    const int zero=0,one=1;

    pre=NULL;
    first=NULL;
    p=root;
    s1.push(p);
    s2.push(zero);
    while(!s1.isEmpty()){
        flag=s2.pop();
        p=s1.top();
        if(flag==1){
            s1.pop();
            //cout<<p->data<<" ";
            if(!first) first=p;
            if(p->rightFlag==0&&p->right){//有右子压右子，没有进入下一轮循环
                s1.push(p->right);
                s2.push(zero);
            }
            //加中序遍历线索
            if(!p->left)  {
                p->leftFlag=1;p->left=pre;
            }

            if(pre&&!(pre->right)){
                pre->rightFlag=1;pre->right=p;
            }
            pre=p;
        }
        else{
            s2.push(one);
            if(p->leftFlag==0&&p->left){
                s1.push(p->left);
                s2.push(zero);
            }
        }
    }
    //遍历序列最后一个结点后继为空
    p->rightFlag=1;
    return first;
}

template <class elemtype>
void binaryTree<elemtype>::ThreadMidVisit(Node<elemtype>*first)const{
    if(!first) return;
    Node<elemtype>*p=first;
    while(p){
        cout<<p->data<<" ";
        //找p的后继元素
        if(p->rightFlag==0){//如果有右子
            p=p->right;
            //沿着右子的左分支一路向左
            while(p->leftFlag==0&&p->left)
                p=p->left;        
        }
        else p=p->right;//无右子，直接用后继线索
    }
    cout<<endl;
}

template <class elemtype>
void binaryTree<elemtype>::ThreadMidPreVisit()const{
    if(!root) return;
    Node<elemtype>*p=root;
    while(p){
        cout<<p->data<<" ";
        if(p->leftFlag==0)
            p=p->left;
        else{
            if(p->rightFlag==0)
                p=p->right;
            else{
                while(p&&(p->rightFlag==1)) p=p->right;
                if(!p) return;
                p=p->right;
            }
        }
    }
    cout<<endl;
}

#endif