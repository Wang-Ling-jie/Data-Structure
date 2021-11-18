#ifndef priorityQueue_h
#define priorityQueue_h

template <class elemtype>
class priorityQueue{
    public:
        priorityQueue(int capacity=100);
        priorityQueue(const elemtype data[],int size);
        ~priorityQueue();
        bool isEmpty()const;
        void enQueue(const elemtype &x);
        elemtype deQueue();
        elemtype getHead()const;
    private:
        int currentSize;    //队列长度
        elemtype *array;
        int maxSize;        //容量

        void buildHeap();
        void doubleSpace();
        void percolateDown(int hole);
};

template <class elemtype>
priorityQueue<elemtype>::priorityQueue(int capacity){
    array=new elemtype[capacity];
    maxSize=capacity;
    currentSize=0;
}

template <class elemtype>
priorityQueue<elemtype>::priorityQueue(const elemtype data[],int size):maxSize(size+10),currentSize(size){
    array=new elemtype[maxSize];
    for(int i=0;i<size;++i)
        array[i+1]=data[i];
    buildHeap();
}

template <class elemtype>
priorityQueue<elemtype>::~priorityQueue(){
    delete []array;
}

template <class elemtype>
bool priorityQueue<elemtype>::isEmpty() const{
    return currentSize==0;
}

template <class elemtype>
elemtype priorityQueue<elemtype>::getHead()const{
    return array[1];
}

template <class elemtype>
void priorityQueue<elemtype>::enQueue(const elemtype &x){
    if(currentSize==maxSize-1) doubleSpace();
    //向上过滤
    int hole=++currentSize;
    for(;hole>1&&x<array[hole/2];hole/=2)
        array[hole]=array[hole/2];
    array[hole]=x;
}

template <class elemtype>
elemtype priorityQueue<elemtype>::deQueue(){
    elemtype minItem;
    minItem=array[1];
    array[1]=array[currentSize--];
    percolateDown(1);
    return minItem;
}

template <class elemtype>
void priorityQueue<elemtype>::percolateDown(int hole){
    int child;
    elemtype tmp=array[hole];
    
    for(;hole*2<=currentSize;hole=child){
        child=hole*2;
        if(child!=currentSize&&array[child+1]<array[child])
            child++;
        if(array[child]<tmp)    array[hole]=array[child];
        else break;    
    }
    array[hole]=tmp;
}

template <class elemtype>
void priorityQueue<elemtype>::buildHeap(){
    for(int i=currentSize/2;i>0;--i){
        percolateDown(i);
    }
}

template <class elemtype>
void priorityQueue<elemtype>::doubleSpace(){
    elemtype*tmp=array;
    maxSize*=2;
    array=new elemtype[maxSize];
    for(int i=0;i<=currentSize;++i)
        array[i]=tmp[i];
    delete []tmp;
}

#endif