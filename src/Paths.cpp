#include "Paths.h"
#include <iostream>

Paths::Paths(Search& searchStrategy) : searchStrategy(searchStrategy){
    edgeTo = new uint32_t[searchStrategy.GetGraph().V()];
    searchStrategy.Run(*this, 0);
}

Paths::~Paths(){
    delete[] edgeTo;
    edgeTo = nullptr;
}

void Paths::Receive(uint32_t v, uint32_t w){
    edgeTo[w] = v;
}

void Paths::Print() const{
    for (uint32_t i = 0; i < searchStrategy.GetGraph().V(); ++i) {
        std::cout << i << " -> " << edgeTo[i] << std::endl;
    }
}