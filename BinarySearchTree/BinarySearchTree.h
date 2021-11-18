#ifndef BinarySearchTree_h
#define BinarySearchTree_h

template <class elemtype>
class BinarySearchTree{
    private:
        struct BinaryNode{
            elemtype data;
            BinaryNode*left;
            BinaryNode*right;

            BinaryNode(const elemtype &thedata,BinaryNode *lt=NULL,BinaryNode *rt=NULL){
                data=thedata;
                left=lt;
                right=rt;
            }
        };
        BinaryNode*root;

    public:
        BinarySearchTree();
        ~BinarySearchTree();
        void insert(const elemtype &x);
        void remove(const elemtype &x);
        elemtype*find(const elemtype &x)const;
    private:
        void insert(const elemtype &x,BinaryNode*&t);
        void remove(const elemtype &x,BinaryNode*&t);
        elemtype*find(const elemtype &x,BinaryNode*t)const;
        void makeEmpty(BinaryNode*t);
};  

template <class elemtype>
elemtype *BinarySearchTree<elemtype>::find(const elemtype &x)const{
    return find(x,root);
}

template <class elemtype>
elemtype *BinarySearchTree<elemtype>::find(const elemtype&x,BinaryNode *t)const{
    if(t==NULL) return NULL;
    if(t->data==x) return &(t->data);
    if(x<t->data) return find(x,t->left);
    else return find(x,t->right);
}

template <class elemtype>
void BinarySearchTree<elemtype>::insert(const elemtype &x,BinaryNode *&t){
    if(t==NULL) t=new BinaryNode(x,NULL,NULL);
    else if(x<t->data)  insert(x,t->left);
    else if(x>t->data)  insert(x,t->right);
}

template<class elemtype>
void BinarySearchTree<elemtype>::insert(const elemtype&x){
    insert(x,root);
}

template<class elemtype>
void BinarySearchTree<elemtype>::remove(const elemtype &x){
    remove(x,root);
}

template <class elemtype>
void BinarySearchTree<elemtype>::remove(const elemtype &x,BinaryNode*&t){
    if(t==NULL) return;
    if(x<t->data)   remove(x,t->left);
    else if(x>t->data)  remove(x,t->right);
    else if(t->left!=NULL&&t->right!=NULL){         //有两个孩子
        BinaryNode*tmp=t->right;
        while(tmp->left!=NULL)  tmp=tmp->left;
        t->data=tmp->data;
        remove(t->data,t->right);
    }
    else{                                           //被删结点为叶子结点或只有一个儿子
            BinaryNode*oldNode=t;
            t=(t->left!=NULL) ? t->left:t->right;
            delete oldNode;
    }
}

template<class elemtype>
BinarySearchTree<elemtype>::BinarySearchTree(){
    root=NULL;
}

template<class elemtype>
BinarySearchTree<elemtype>::~BinarySearchTree(){
    makeEmpty(root);
}

template <class elemtype>
void BinarySearchTree<elemtype>::makeEmpty(BinaryNode*t){
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
}

#endif