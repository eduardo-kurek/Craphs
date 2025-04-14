#include <iostream>
#include "Graph.h"
#include "DeepSearch.h"
#include "BreadthFirstSearch.h"
#include "Paths.h"

int main(){
    Graph g(13);
    g.AddEdge(0, 5);
    g.AddEdge(4, 3);
    g.AddEdge(0, 1);
    g.AddEdge(9, 12);
    g.AddEdge(6, 4);
    g.AddEdge(5, 4);
    g.AddEdge(0, 2);
    g.AddEdge(11, 12);
    g.AddEdge(9, 10);
    g.AddEdge(0, 6);
    g.AddEdge(7, 8);
    g.AddEdge(9, 11);
    g.AddEdge(5, 3);

    Paths<BreadthFirstSearch> path(g);
    path.Search(3);

    std::cout << path << std::endl;

    path.Search(1);

    std::cout << path << std::endl;

    //std::cout << g << std::endl;

    return 0;
}