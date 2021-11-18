#include <iostream>
#include "BinarySearchTree.h"

using namespace std;
int main(){
    BinarySearchTree<int>bst;
    bst.insert(2);
    bst.insert(8);
    if(bst.find(5)) cout<<"find 5";
    if(bst.find(2)) cout<<"find 2";
}