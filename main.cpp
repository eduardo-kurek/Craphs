#include <iostream>
#include "Graph.h"

int main(){
    Graph g(6);
    g.AddEdge(0, 5);
    g.AddEdge(2, 4);
    g.AddEdge(2, 3);
    g.AddEdge(1, 2);
    g.AddEdge(0, 1);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(0, 2);
    
    std::cout << g << std::endl;
    return 0;
}