#ifndef seqQueue_h
#define seqQueue_h

template <class elemtype>
class seqQueue{
    private:
        elemtype *data;
        int maxsize;
        int front,rear;
        void doublespace();
    public:
        seqQueue(int size=10);
        ~seqQueue(){delete []data;};
        bool isEmpty()const;
        void enQueue(const elemtype &x);
        elemtype deQueue();
        elemtype getHead()const;
};

template <class elemtype>
seqQueue<elemtype>::seqQueue(int size){
    data=new elemtype[size];
    maxsize=size;
    front=rear=0;
}

template <class elemtype>
bool seqQueue<elemtype>::isEmpty()const{
    return (front==rear);
}

template <class elemtype>
void seqQueue<elemtype>::enQueue(const elemtype& x){
    if((rear+1)%maxsize==front)    doublespace();
    rear=(rear+1)%maxsize;
    data[rear]=x;
}

template <class elemtype>
elemtype seqQueue<elemtype>::deQueue(){
    if(front==rear) exit(-1);
    front=(front+1)%maxsize;
    return data[front];
}

template <class elemtype>
elemtype seqQueue<elemtype>::getHead()const{
    return data[(front+1)%maxsize];
}

template <class elemtype>
void seqQueue<elemtype>::doublespace(){
    elemtype*tmp=data;
    data=new elemtype[maxsize*2];
    for(int i=1;i<maxsize;++i){
        data[i]=tmp[(i+front)%maxsize];
    }
    front=0;
    rear=maxsize-1;
    maxsize*=2;
    delete []tmp;
}

#endif