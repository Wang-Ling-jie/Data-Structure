#include <iostream>
#include "linkstack.h"
using namespace std;

int main(){
    linkStack<int> sta;
    sta.push(4);
    sta.push(3);
    sta.push(5);
    cout<<sta.top()<<endl;
    cout<<sta.pop()<<endl;
    cout<<sta.pop()<<endl;
    cout<<sta.pop()<<endl;
    return 0;
}