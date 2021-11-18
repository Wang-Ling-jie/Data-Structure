#ifndef RedBlackTree_h
#define RedBlackTree_h

template <class KEY, class OTHER>
struct SET{
    KEY key;
    OTHER other;
};


template <class KEY,class OTHER>
class RedBlackTree{
    enum colorT{RED,BLACK};
    struct RedBlackNode{
        SET<KEY,OTHER> data;
        RedBlackNode *left;
        RedBlackNode *right;
        colorT color;

        RedBlackNode(const SET<KEY,OTHER>&element,RedBlackNode *lt=NULL,RedBlackNode*rt=NULL,colorT h=RED)
        :data(element),left(lt),right(rt),color(h){}
    };

    RedBlackNode*root;

public:
    RedBlackTree(RedBlackNode*t=NULL){root=t;}
    ~RedBlackTree(){makeEmpty(root);};
    SET<KEY,OTHER>*find(const KEY&x)const;
    void insert(const SET<KEY,OTHER>&x);
    void remove(const KEY &x);
private:
    void makeEmpty(RedBlackNode*t);
    void insertAdjust(RedBlackNode*gp,RedBlackNode*p,RedBlackNode*t);
    void removeAdjust(RedBlackNode*&p,RedBlackNode*&c,RedBlackNode*&t,KEY del);
    void LL(RedBlackNode*gp);
    void LR(RedBlackNode*gp);
    void RL(RedBlackNode*gp);
    void RR(RedBlackNode*gp);
};

template <class KEY,class OTHER>
SET<KEY,OTHER>*RedBlackTree<KEY,OTHER>::find(const KEY&x)const{
    RedBlackNode *t=root;
    while(t!=NULL&&t->data.key!=x){
        if(t->data.key>x) t=t->left;
        else t=t->right;
    }
    if(t==NULL) return NULL;
    else return &(t->data);
}

template<class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::makeEmpty(RedBlackNode *t){
    if(t==NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::insert(const SET<KEY,OTHER>&x){
    RedBlackNode *t,*parent,*grandP;

    if(root==NULL){     //在空树上插入
        root=new RedBlackNode(x,NULL,NULL,BLACK);
        return;
    }
    parent=grandP=t=root;
    while(true){
        if(t){
            if(t->left&&t->left->color==RED&&t->right&&t->right->color==RED){
                t->left->color=t->right->color=BLACK;
                t->color=RED;
                insertAdjust(grandP,parent,t);
            }
            grandP=parent;
            parent=t;
            t=(t->data.key>x.key?t->left:t->right);
        }
        else{
            t=new RedBlackNode(x);
            if(x.key<parent->data.key)  parent->left=t;else parent->right=t;
            insertAdjust(grandP,parent,t);
            root->color=BLACK;
            return;
        }
    }
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::insertAdjust(RedBlackNode*gp,RedBlackNode*p,RedBlackNode*t){
    if(p->color==BLACK)     return;    //没有出现连续红结点
    if(p==root){
        p->color=BLACK;
        return;
    }
    if(gp->left==p){
        if(p->left==t)  LL(gp);
        else LR(gp);
    }
    else {
        if(p->right==t) RR(gp);
        else RL(gp);
    }
}

template <class KEY, class OTHER>
void RedBlackTree<KEY,OTHER>::LL(RedBlackNode*gp){  //交换gp和p的值
    RedBlackNode*p=gp->left,*t=p->left;
    RedBlackNode tmp=*gp;
    gp->data=p->data;
    gp->left=t;
    gp->right=p;
    p->data=tmp.data;
    p->left=p->right;
    p->right=tmp.right;
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::LR(RedBlackNode*gp){  //交换gp和t的值
    RedBlackNode *p=gp->left,*t=p->right;
    RedBlackNode tmp=*gp;
    gp->data=t->data;
    gp->right=t;
    p->right=t->left;
    t->data=tmp.data;
    t->left=t->right;
    t->right=tmp.right;
}

template <class KEY, class OTHER>
void RedBlackTree<KEY,OTHER>::RR(RedBlackNode*gp){
    RedBlackNode *p=gp->right,*t=p->right;
    RedBlackNode tmp=*gp;
    gp->data=p->data;
    gp->right=t;
    gp->left=p;
    p->data=tmp.data;
    p->right=p->left;
    p->left=tmp.left;
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::RL(RedBlackNode*gp){
    RedBlackNode *p=gp->right,*t=p->left;
    RedBlackNode tmp=*gp;
    gp->data=t->data;
    gp->left=t;
    p->left=t->right;
    t->data=tmp.data;
    t->right=t->left;
    t->left=tmp.left;
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::remove(const KEY &x){
    KEY del=x;
    RedBlackNode *t,*p,*c;  //c为当前结点，p为父结点，t为兄弟结点

    if(root==NULL) return;
    if(root->data.key==x&&root->left==NULL&&root->right==NULL){
        delete root;
        root=NULL;
        return;
    }

    p=c=t=root;
    while(true){
        removeAdjust(p,c,t,del);
        if(c->data.key==del&&c->left&&c->right){
            RedBlackNode*tmp=c->right;
            while(tmp->left) tmp=tmp->left;
            c->data=tmp->data;
            del=tmp->data.key;
            p=c;
            c=c->right;
            t=p->left;
            continue;
        }
        
        if(c->data.key==del){
            if(p->left==c)  p->left=NULL; else p->right=NULL;
            delete c;
            root->color=BLACK;
            return;
        }
        p=c;
        c=(del<p->data.key?p->left:p->right);
        t=(c==p->left?p->right:p->left);
    }
}

template <class KEY,class OTHER>
void RedBlackTree<KEY,OTHER>::removeAdjust(RedBlackNode*&p,RedBlackNode*&c,RedBlackNode*&t,KEY del){
    if(c->color==RED)     return;
    if(c==root)
        if(c->left&&c->right&&c->right->color==c->left->color){
            c->color=RED;
            c->left->color=c->right->color=BLACK;
            return;
        }
    
    if(((c->left&&c->left->color==BLACK)||c->left==NULL)&&((c->right&&c->right->color==BLACK)||c->right==NULL))
        if(((t->left&&t->left->color==BLACK)||t->left==NULL)&&((t->right&&t->right->color==BLACK)||t->right==NULL)){
            p->color=BLACK;
            t->color=c->color=RED;
        }
        else{
            if(p->left==t)
                if(t->left&&t->left->color==RED){
                    t->left->color=BLACK;
                    LL(p);
                    p=t;
                }
                else {
                    LR(p);
                    p=p->right;
                    p->color=BLACK;
                }
            else if(t->right&&t->right->color==RED){
                t->right->color=BLACK;
                RR(p);
                p=t;
            }
            else{
                RL(p);
                p=p->left;
                p->color=BLACK;
            }
            c->color=RED;
        }
    else{
            if(c->data.key==del){
                if(c->left&&c->right){
                    if(c->right->color==BLACK){
                        LL(c);
                        c=c->right;
                    }
                    return;
                }
                if(c->left){
                    LL(c);
                    p=c;
                    c=c->right;
                }
                else{
                    RR(c);
                    p=c;
                    c=c->left;
                }
            }
            else{
                p=c;
                c=(del<p->data.key?p->left:p->right);
                t=(c==p->left?p->right:p->left);
                if(c->color==BLACK){
                    if(t==p->right) RR(p);else LL(p);
                    p=t;
                    t=(c==p->left?p->right:p->left);
                    removeAdjust(p,c,t,del);
                }
            }
    }
}



#endif