#include "graphs/imp/AdjacentListGraph.h"

AdjacentListGraph::AdjacentListGraph(uint32_t vertices){
    adjList = new std::forward_list<uint32_t>[vertices];
}

AdjacentListGraph::~AdjacentListGraph(){
    delete[] adjList;
}

void AdjacentListGraph::AddEdge(uint32_t v, uint32_t w){
    adjList[v].push_front(w);
}

bool AdjacentListGraph::IsConnected(uint32_t v, uint32_t w) const{
    for(auto i : adjList[v]){
        if(i == w){
            return true;
        }
    }
    return false;
}

const std::forward_list<uint32_t>& AdjacentListGraph::Adj(uint32_t v) const{
    return adjList[v];
}

