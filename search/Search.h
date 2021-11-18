#ifndef find_h
#define find_h

template <class KEY, class OTHER>
struct SET{
    KEY key;
    OTHER other;
};

template <class KEY,class OTHER>
int seqSearch(SET<KEY,OTHER>data[],int size,const KEY &x)
{
    int i;
    data[0].key=x;
    for(i=size;x<data[i].key;--i);
    if(x<data[i].key||i==0) return 0;
    else return i;
}

template<class KEY, class OTHER>
int binarySearch(SET<KEY,OTHER>data[],int size,const KEY&x){
    int low=1,high=size,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(x==data[mid].key) return mid;
        if(x<data[mid].key) high=mid-1;
        else low=mid+1;
    }
    return 0;
}



#endif