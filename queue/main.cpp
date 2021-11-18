#include "linkQueue.h"
#include <iostream>

using namespace std;
int main(){
    linkQueue<int>que;
    que.enQueue(2);
    cout<<que.isEmpty()<<endl;
    que.enQueue(3);
    que.enQueue(4);
    que.enQueue(5);
    cout<<que.deQueue()<<endl;
    cout<<que.deQueue()<<endl;
    cout<<que.deQueue()<<endl;
    cout<<que.deQueue()<<endl;
    cout<<que.isEmpty();
    return 0;
}