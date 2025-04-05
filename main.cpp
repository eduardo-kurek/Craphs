#include <iostream>
#include "Graph.h"
#include "DeepSearch.h"
#include "Paths.h"

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

    Paths<DeepSearch> path(g);

    auto pathTo5 = path.PathTo(5);
    std::cout << "Path to 1: ";
    for (const auto& vertex : pathTo5) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::cout << path << std::endl;

    //std::cout << g << std::endl;
    return 0;
}