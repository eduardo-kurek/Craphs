#include "DeepSearch.h"
#include <iostream>

DeepSearch::DeepSearch(const Graph &graph) : Search(graph){ }

void DeepSearch::Run(Visitor& visitor, uint32_t s){
    graph.CheckVertex(s);
    ClearMarkeds();
    visitor.Clear();
    visitor.Receive(-1, s);
    DeepSearchRecursive(visitor, s);
}

void DeepSearch::DeepSearchRecursive(Visitor& visitor, uint32_t v){
    Mark(v);
    for(auto w : graph.Adj(v)){
        if(!marked[w]){
            visitor.Receive(v, w);
            DeepSearchRecursive(visitor, w);
        }
    }
}
