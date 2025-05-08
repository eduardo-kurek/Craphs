#include <iostream>

#include "graphs/Graph.h"
#include "cc/GraphCC.h"
#include "visitors/Paths.h"
#include "search/DeepSearch.h"

int main(){
    Graph g(3);
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);

    std::cout << g << std::endl;

    Paths<DeepSearch> paths(g, 0);

    std::cout << paths << std::endl;
    

    // Paths<BreadthFirstSearch> path(g);
    // path.Search(3);

    // std::cout << path << std::endl;

    // path.Search(1);

    // std::cout << path << std::endl;

    // std::cout << g << std::endl;

    return 0;
}