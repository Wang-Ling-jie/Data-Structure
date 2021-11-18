#include <iostream>
#include "openHashTable.h"

using namespace std;
int main(){
    SET<int,char*>a[]={{10,"aaa"},{8,"bbb"},{21,"ccc"},{87,"ddd"},{56,"eee"},{4,"fff"},{11,"ggg"},{3,"hhh"},{22,"iii"},{7,"jjj"}};
    openHashTable<int,char*>tree;
    SET<int,char*>*p;

    for(int i=0;i<10;++i) tree.insert(a[i]);
    p=tree.find(21);
    if(p) cout<<"find 21 is "<<p->key<<" "<<p->other<<endl;
    else cout<<"not found"<<endl;
    tree.remove(21);
    p=tree.find(21);
    if(p) cout<<"find 21 is "<<p->key<<" "<<p->other<<endl;
    else cout<<"not found"<<endl;

    return 0;
}