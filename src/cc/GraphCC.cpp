#include "cc/GraphCC.h"
#include "visitors/Paths.h"
#include "search/DeepSearch.h"
#include <iostream>

GraphCC::GraphCC(const Graph* graph) : CC(graph) {
    
}

void GraphCC::Run(){
    std::cout << "Running top" << std::endl;
}