#include <iostream>
#include "Digraph.h"
#include "DeepSearch.h"
#include "BreadthFirstSearch.h"
#include "Paths.h"

int main(){
    Digraph g(13);
    g.AddEdge(0, 1);
    g.AddEdge(0, 5);
    g.AddEdge(2, 3);
    g.AddEdge(2, 0);
    g.AddEdge(3, 2);
    g.AddEdge(3, 5);
    g.AddEdge(5, 4);
    g.AddEdge(6, 4);
    g.AddEdge(6, 8);
    g.AddEdge(6, 4);
    g.AddEdge(6, 9);
    g.AddEdge(7, 9);
    g.AddEdge(7, 6);
    g.AddEdge(8, 6);
    g.AddEdge(9, 10);
    g.AddEdge(9, 11);
    g.AddEdge(10, 12);
    g.AddEdge(11, 12);
    g.AddEdge(11, 4);
    g.AddEdge(12, 9);

    Paths<BreadthFirstSearch> path(g);
    path.Search(3);

    std::cout << path << std::endl;

    // path.Search(1);

    // std::cout << path << std::endl;

    // std::cout << g << std::endl;

    return 0;
}