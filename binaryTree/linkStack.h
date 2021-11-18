#ifndef linkstack_h
#define linkstack_h

#include <iostream>
using namespace std;

template <class elemtype>
class linkStack{
    private:
        struct node{
            elemtype data;
            node*next;
            node(const elemtype &x,node*N=NULL){data=x;next=N;}
            node():next(NULL){}
            ~node(){};
        };
    node*Top;
    public:
        linkStack();
        ~linkStack();
        bool isEmpty()const;
        void push(const elemtype &x);
        elemtype pop();
        elemtype top()const;
};

template <class elemtype>
linkStack<elemtype>::linkStack(){
    Top=NULL;
}

template <class elemtype>
linkStack<elemtype>::~linkStack(){
    node*p=Top;
    while(Top!=NULL){
        Top=Top->next;
        delete p;
        p=Top;        
    }
}

template <class elemtype>
bool linkStack<elemtype>::isEmpty()const{
    return Top==NULL;
}

template <class elemtype>
void linkStack<elemtype>::push(const elemtype &x){
    Top=new node(x,Top);
}

template <class elemtype>
elemtype linkStack<elemtype>::pop(){
    node*tmp=Top;
    elemtype x=tmp->data;
    Top=Top->next;
    delete tmp;
    return x;
}

template <class elemtype>
elemtype linkStack<elemtype>::top()const{
    return Top->data;
}

#endif