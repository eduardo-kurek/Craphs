#include "search/DeepSearch.h"
#include <iostream>

DeepSearch::DeepSearch(const IGraph<IEdge>& graph) : Search(graph){ }

void DeepSearch::Run(Visitor& visitor, uint32_t s){
    graph.CheckVertex(s);
    ClearMarkeds();
    visitor.Clear();
    visitor.Receive(-1, s, 0);
    DeepSearchRecursive(visitor, s, 0);
}

void DeepSearch::DeepSearchRecursive(Visitor& visitor, uint32_t v, uint32_t dist){
    Mark(v);
    for(auto e : graph.Adj(v)){
        if(!marked[e.Other()]){
            visitor.Receive(v, e.Other(), dist);
            DeepSearchRecursive(visitor, e.Other(), dist+1);
        }
    }
}
