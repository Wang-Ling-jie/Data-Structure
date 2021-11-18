#include <iostream>
#include "dlinklist.h"
using namespace std;

int main()
{
    dlinkList<int> lis;
    lis.insert(0,8);
    lis.insert(1,4);
    lis.insert(0,7);
    lis.insert(0,9);
    lis.traverse();
    cout<<"visit"<<lis.visit(2)<<endl;
    lis.remove(2);
    lis.traverse();
    lis.remove(0);
    lis.traverse();
    cout<<"search"<<lis.search(4);
    return 0;
}
