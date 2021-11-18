#include <iostream>
#include "adjMatrixGraph.h"
using namespace std;

int main()
{
    int a[5] = {4, 5, 6, 7, 8};
    adjMatrixGraph<int, int> graph(5, a, -1);
    cout << graph.exist(5, 5) << " " << graph.exist(4, 6);
    graph.insert(4, 5, 7);
    cout << graph.exist(4, 5);
    graph.remove(4, 5);
    cout << graph.exist(4, 5);
}