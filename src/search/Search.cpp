#include "search/Search.h"

Search::Search(const Graph& graph) : graph(graph){
    marked = new bool[graph.V()];
    ClearMarkeds();
}

Search::~Search(){
    delete[] marked;
    marked = nullptr;
}

void Search::ClearMarkeds(){
    for (uint32_t i = 0; i < graph.V(); ++i) {
        marked[i] = false;
    }
}

void Search::Mark(uint32_t v){
    marked[v] = true;
}

bool Search::HasPathTo(const uint32_t v) const{
    graph.CheckVertex(v);
    return marked[v];
}
