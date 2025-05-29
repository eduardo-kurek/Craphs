#pragma once

#include "graphs/imp/GraphImp.h"
#include "edges/IEdge.h"

template <EdgeType T>
class AdjacentListGraph final : public GraphImp<T> {

    std::forward_list<T>* adjList;

public:
    explicit AdjacentListGraph(uint32_t vertices){
        adjList = new std::forward_list<T>[vertices];
    }

    ~AdjacentListGraph() override{
        delete[] adjList;
        adjList = nullptr;
    }

    void AddEdge(uint32_t v, T edge) override{
        adjList[v].push_front(edge);
    }

    bool IsConnected(uint32_t v, uint32_t w) const override{
        for(auto i : adjList[v])
            if(i == w)
                return true;
        return false;
    }

    const std::forward_list<uint32_t>& Adj(uint32_t v) const override{
        return adjList[v];
    }
    
};