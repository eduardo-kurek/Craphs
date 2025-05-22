#include <iostream>

#include "graphs/Graph.h"
#include "search/BreadthFirstSearch.h"
#include "search/DeepSearch.h"
#include "visitors/Paths.h"
#include "algorithms/Eccentricity.h"

#define LOG(x) std::cout << x << std::endl;

int main(){

    const Graph g = Graph::FromGEXF("../LesMiserables.gexf");
    // Graph g(13);
    // g.AddEdge(0, 5);
    // g.AddEdge(4, 3);
    // g.AddEdge(0, 1);
    // g.AddEdge(9, 12);
    // g.AddEdge(6, 4);
    // g.AddEdge(5, 4);
    // g.AddEdge(0, 2);
    // g.AddEdge(11, 12);
    // g.AddEdge(9, 10);
    // g.AddEdge(0, 6);
    // g.AddEdge(7, 8);
    // g.AddEdge(9, 11);
    // g.AddEdge(5, 3);

    Eccentricity eccentricity(g);
    LOG(eccentricity);

    return 0;
}