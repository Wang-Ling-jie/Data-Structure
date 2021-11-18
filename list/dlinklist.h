#ifndef dlinklist_h
#define dlinklist_h

#include <iostream>
using namespace std;

template <class elemtype>
class dlinkList
{
private:
    struct node
    {
        elemtype data;
        node *prev,*next;
        node(const elemtype&x,node*p=NULL,node*n=NULL){prev=p;next=n;data=x;}
        node():next(NULL),prev(NULL){}
        ~node(){};
    };
    node *head,*tail;
public:
    dlinkList();
    ~dlinkList();
    void insert(int i,const elemtype &x);
    void remove(int i);
    void clear();
    int length()const;
    int search(const elemtype&x)const;
    elemtype visit(int i)const;
    void traverse()const;
};

template <class elemtype>
dlinkList<elemtype>::dlinkList(){
    head=new node;
    head->next=tail=new node();
    tail->prev=head;
}

template <class elemtype>
void dlinkList<elemtype>::clear(){
    node *p=head->next;
    node *q;
    head->next=tail;
    tail->prev=head;
    while(p!=tail){
        q=p->next;
        delete p;
        p=q;
    }
}

template <class elemtype>
dlinkList<elemtype>::~dlinkList(){
    clear();
    delete head;
    delete tail;
}

template <class elemtype>
void dlinkList<elemtype>::insert(int i,const elemtype &x){
    node* p=head;
    while(i-->0&&p->next) p=p->next;
    if(!(p->next)) return;
    node *tmp=new node(x,p,p->next);
    p->next->prev=tmp;
    p->next=tmp;
}

template <class elemtype>
void dlinkList<elemtype>::remove(int i){
    node *p=head;
    while(i-->=0&&p->next) p=p->next;
    if(!(p->next)) return;
    p->prev->next=p->next;
    p->next->prev=p->prev;
    delete p;
}

template <class elemtype>
int dlinkList<elemtype>::length()const{
    node *p=head->next;
    int len=0;
    while(p!=tail){
        p=p->next;
        len++;
    }
    return len;
}

template <class elemtype>
int dlinkList<elemtype>::search(const elemtype &x)const{
    node *p=head->next;
    int j=0;
    while(p!=tail){
        if(p->data==x)  return j;
        j++;
        p=p->next;
    }
    if(p==tail)  return -1;
}

template <class elemtype>
elemtype dlinkList<elemtype>::visit(int i)const{
    node *p=head;
    while(i-->=0&&p){
        p=p->next;
    }
    if(!p) exit(-1);
    return p->data;
}

template <class elemtype>
void dlinkList<elemtype>::traverse()const{
    node *p=head->next;
    while(p!=tail){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

#endif // dlinklist_h
