#include <iostream>
#include "binaryTree.h"
using namespace std;

int main(){
    binaryTree<char>tree;
    cout<<tree.isEmpty()<<endl;
    tree.createTree('@');
    tree.preOrder();
    tree.PreOrder();
    tree.inOrder();
    tree.InOrder();
    tree.midOrder();
    tree.postOrder();
    tree.PostOrder();
    tree.LevelOrder();
    cout<<tree.isEmpty()<<endl;
    Node<char>*first=tree.ThreadMid();
    cout<<"thread mid visit: ";
    tree.ThreadMidVisit(first);
    cout<<"thread mid pre visit: ";
    tree.ThreadMidPreVisit();
    return 0;
}