#pragma once

#include "visitors/Visitor.h"
#include "search/Search.h"
#include <unordered_map>
#include <stdexcept>
#include <concepts>
#include <cstdint>
#include <vector>
#include <stack>

template <class T>
requires std::derived_from<T, Search>
class Paths : public Visitor {

private:
    const Graph& graph;
    T searcher;

    uint32_t* edgeTo = nullptr;
    uint32_t startVertex;

    std::stack<uint32_t> GetPathStack(uint32_t v) const{
        std::stack<uint32_t> pathStack;
        for(uint32_t x = v; x != startVertex; x = edgeTo[x])
            pathStack.push(x);
        pathStack.push(startVertex);
        return pathStack;
    }

    std::vector<uint32_t> GetPathVector(std::stack<uint32_t>& v) const{
        std::vector<uint32_t> pathVector;
        while(!v.empty()){
            pathVector.push_back(v.top());
            v.pop();
        }
        return pathVector;
    }
    
public:
    Paths(const Graph& graph, uint32_t startVertex) 
        : graph(graph), searcher(graph), startVertex(startVertex)
    {
        edgeTo = new uint32_t[graph.V()]();
        searcher.Run(*this, startVertex);
    }

    ~Paths() override{
        delete[] edgeTo;
        edgeTo = nullptr;
    }

    void Receive(uint32_t v, uint32_t w) override{
        edgeTo[w] = v;
    }

    std::vector<uint32_t> PathTo(uint32_t v) const{
        graph.CheckVertex(v);
        if(!searcher.HasPathTo(v)) return std::vector<uint32_t>();
        auto pathStack = GetPathStack(v);
        return GetPathVector(pathStack);
    }

    bool HasPathTo(uint32_t v) const{
        return searcher.HasPathTo(v);
    }

    friend std::ostream& operator<<(std::ostream& os, const Paths& paths){
        os << "Vertex -> EdgeTo" << std::endl;
        for(uint32_t i = 0; i < paths.graph.V(); i++){
            os << i << " -> " << paths.edgeTo[i] << std::endl;
        }
        return os;
    }

};