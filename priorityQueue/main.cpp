#include <iostream>
#include "priorityQueue.h"

using namespace std;
int main(){
    priorityQueue<int>que;
    for(int i=100;i>0;--i){
        que.enQueue(i);
    }
    while(!que.isEmpty()){
        cout<<que.deQueue()<<' ';
    }
}