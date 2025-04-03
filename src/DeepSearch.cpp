#include "DeepSearch.h"
#include <iostream>

DeepSearch::DeepSearch(const Graph &graph) : Search(graph){
    marked = new bool[graph.V()];
    ClearMarkeds();
}

void DeepSearch::ClearMarkeds(){
    for (uint32_t i = 0; i < graph.V(); ++i)
        marked[i] = false;
}

DeepSearch::~DeepSearch(){
    delete[] marked;
    marked = nullptr;
}

void DeepSearch::Run(Visitor& visitor, uint32_t s){
    graph.CheckVertex(s);
    ClearMarkeds();
    visitor.Clear();
    visitor.Receive(-1, s);
    DeepSearchRecursive(visitor, s);
}

void DeepSearch::DeepSearchRecursive(Visitor& visitor, uint32_t v){
    marked[v] = true;
    for(auto w : graph.Adj(v)){
        if(!marked[w]){
            visitor.Receive(v, w);
            DeepSearchRecursive(visitor, w);
        }
    }
}

bool DeepSearch::HasPathTo(uint32_t v) const{
    graph.CheckVertex(v);
    return marked[v];
}
