#include "Paths.h"
#include <iostream>

Paths::Paths(Search& searchStrategy, uint32_t startVertex) 
    : searchStrategy(searchStrategy), startVertex(startVertex)
{
    edgeTo = new uint32_t[searchStrategy.GetGraph().V()];
    searchStrategy.Run(*this, startVertex);
}

Paths::~Paths(){
    delete[] edgeTo;
    edgeTo = nullptr;
}

void Paths::Receive(uint32_t v, uint32_t w){
    edgeTo[w] = v;
}

std::vector<uint32_t> Paths::PathTo(const uint32_t v){
    searchStrategy.GetGraph().CheckVertex(v);
    if(!searchStrategy.HasPathTo(v)) return std::vector<uint32_t>();
    auto pathStack = GetPathStack(v);
    return GetPathVector(pathStack);
}

std::stack<uint32_t> Paths::GetPathStack(const uint32_t v){
    std::stack<uint32_t> pathStack;
    for(uint32_t x = v; x != startVertex; x = edgeTo[x])
        pathStack.push(x);
    pathStack.push(startVertex);
    return pathStack;
}

std::vector<uint32_t> Paths::GetPathVector(std::stack<uint32_t>& stack){
    std::vector<uint32_t> pathVector;
    while(!stack.empty()){
        pathVector.push_back(stack.top());
        stack.pop();
    }
    return pathVector;
}

void Paths::Print() const{
    for (uint32_t i = 0; i < searchStrategy.GetGraph().V(); ++i) {
        std::cout << i << " -> " << edgeTo[i] << std::endl;
    }
}