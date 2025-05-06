#include <iostream>

#include "graphs/Graph.h"

int main(){
    Graph g(3);
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);

    std::cout << g << std::endl;

    // Paths<BreadthFirstSearch> path(g);
    // path.Search(3);

    // std::cout << path << std::endl;

    // path.Search(1);

    // std::cout << path << std::endl;

    // std::cout << g << std::endl;

    return 0;
}