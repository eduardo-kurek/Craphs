#include <iostream>

#include "algorithms/BetweennessCentrality.h"
#include "graphs/Graph.h"
#include "edges/Edge.h"

int main(){
    const Graph<Edge> g = Graph<Edge>::FromGEXF("../LesMiserables.gexf");
    const BetweennessCentrality bc(g);
    bc.Print(std::cout);
    return 0;
}


