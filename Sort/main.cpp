#include <iostream>
#include "Sort.h"
using namespace std;

int main(){
    SET<int,char*>a[]={{10,"aaa"},{8,"bbb"},{10,"ccc"},{87,"ddd"},{56,"eee"},{10,"fff"},{11,"ggg"},{8,"hhh"},{22,"iii"},{7,"jjj"}};
    mergeSort(a,10);
    for(int i=0;i<10;++i) 
        cout<<a[i].key<<" "<<a[i].other<<" ";
}