#ifndef linkQueue_h
#define linkQueue_h

#include <iostream>
using namespace std;
template <class elemtype>
class linkQueue{
    struct node{
        elemtype data;
        node *next;
        node():next(NULL){};
        node(const elemtype &x,node*N=NULL){data=x;next=N;}
        ~node(){}
    };
    node *front,*rear;
    public:
        linkQueue();
        ~linkQueue();
        bool isEmpty()const;
        elemtype getHead()const;
        elemtype deQueue();
        void enQueue(const elemtype &x);
};

template <class elemtype>
linkQueue<elemtype>::linkQueue(){
    front=rear=NULL;
}

template <class elemtype>
linkQueue<elemtype>::~linkQueue(){
    node *tmp;
    while(front){
        tmp=front;
        front=front->next;
        delete tmp;
    }
}

template <class elemtype>
elemtype linkQueue<elemtype>::getHead()const{
    return front->data;
}

template <class elemtype>
elemtype linkQueue<elemtype>::deQueue(){
    node*tmp=front;
    elemtype x=front->data;
    front=front->next;
    if(front==NULL)  rear=NULL; //出队后为空队列
    delete tmp;
    return x;
}

template <class elemtype>
void linkQueue<elemtype>::enQueue(const elemtype& x){
    if(rear==NULL) 
        front=rear=new node(x);
    else
        rear=rear->next=new node(x);
}

template <class elemtype>
bool linkQueue<elemtype>::isEmpty()const{
    return (front==NULL);
}

#endif