#pragma once

#include "graphs/imp/GraphImp.h"
#include "edges/IEdge.h"

template <EdgeType E>
class AdjacentListGraph final : public GraphImp<E> {

    std::forward_list<E>* adjList;

public:
    explicit AdjacentListGraph(uint32_t vertices){
        adjList = new std::forward_list<E>[vertices];
    }

    ~AdjacentListGraph() override{
        delete[] adjList;
        adjList = nullptr;
    }

    void AddEdge(uint32_t v, E&& edge) override{
        adjList[v].push_front(std::move(edge));
    }

    bool IsConnected(uint32_t v, uint32_t w) const override{
        for(auto i : adjList[v])
            if(i.Other() == w)
                return true;
        return false;
    }

    const std::forward_list<E>& Adj(uint32_t v) const override{
        return adjList[v];
    }
    
};