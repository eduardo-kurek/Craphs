#include "Paths.h"
#include <iostream>

Paths::Paths(const Graph& graph) : graph(graph){
    edgeTo = new uint32_t[graph.V()];
    Clear();
}

Paths::~Paths(){
    delete[] edgeTo;
    edgeTo = nullptr;
}

void Paths::Receive(uint32_t v, uint32_t w){
    edgeTo[w] = v;
}

void Paths::Print() const{
    for (uint32_t i = 0; i < graph.V(); ++i) {
        std::cout << i << " -> " << edgeTo[i] << std::endl;
    }
}