#ifndef seqStack_h
#define seqStack_h

template <class elemtype>
class seqStack
{
private:
    elemtype *data;
    int Top;
    int maxsize;
    void doublespace();
public:
    seqStack(int initsize=10);
    ~seqStack(){delete []data;}
    bool isEmpty()const;
    void push(const elemtype &x);
    elemtype pop();
    elemtype top()const;
};

template<class elemtype>
seqStack<elemtype>::seqStack(int initsize){
    maxsize=initsize;
    data=new elemtype[maxsize];
    Top=-1;
}

template <class elemtype>
bool seqStack<elemtype>::isEmpty()const{
    return Top==-1;
}

template <class elemtype>
void seqStack<elemtype>::push(const elemtype &x){
    if(Top==maxsize-1)    doublespace();
    data[++Top]=x;
}

template <class elemtype>
elemtype seqStack<elemtype>::pop(){
    if(Top>-1)
        return data[Top--];
    exit(-1);
}

template <class elemtype>
elemtype seqStack<elemtype>::top()const{
    return data[Top];
}

template <class elemtype>
void seqStack<elemtype>::doublespace(){
    elemtype *tmp=new elemtype[2*maxsize];
    for(int i=0;i<maxsize;++i){
        data[i]=tmp[i];
    }
    delete []data;
    data=tmp;
}

#endif