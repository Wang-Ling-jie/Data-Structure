#include <iostream>
#include "search.h"

using namespace std;
int main(){
    SET<int,int> b[9]={{3,1},{4,4},{43,4},{44,5},{322,31},{444,43},{777,89},{999,33},{3122,321}};
    cout<<binarySearch(b,8,44);
}