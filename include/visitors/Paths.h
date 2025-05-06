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
    uint32_t* startVertexes = nullptr;
    std::unordered_map<uint32_t, uint32_t> idMap;

    uint32_t lastId = 0;
    uint32_t currStartVertex;

    std::stack<uint32_t> GetPathStack(uint32_t v) const{
        std::stack<uint32_t> pathStack;
        uint32_t startVertex = GetStartVertex(v).value();
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

    void UpdateCurrentStartVertex(uint32_t v){ currStartVertex = v; }
    
    void MapId(uint32_t v){
        if(Searched(v)) UpdateId(v);
        else NewId(v);
    }

    void UpdateId(uint32_t v){ idMap[v] = GetId(v).value(); }
    void NewId(uint32_t v){ idMap[v] = lastId; lastId++; }
    

public:
    Paths(const Graph& graph) 
        : graph(graph), searcher(graph)
    {
        edgeTo = new uint32_t[graph.V()]();
        startVertexes = new uint32_t[graph.V()];
        std::fill(startVertexes, startVertexes + graph.V(), -1);
    }

    ~Paths() override{
        delete[] edgeTo;
        edgeTo = nullptr;
    }

    void Search(uint32_t startVertex){
        UpdateCurrentStartVertex(startVertex);
        MapId(startVertex);
        searcher.Run(*this, startVertex);
    }

    void Receive(uint32_t v, uint32_t w) override{
        edgeTo[w] = v;
        startVertexes[w] = currStartVertex;
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

    std::optional<uint32_t> GetStartVertex(uint32_t v) const{
        graph.CheckVertex(v);
        if(Searched(v))
            return startVertexes[v];
        return {};
    }

    std::optional<uint32_t> GetId(uint32_t v) const{
        graph.CheckVertex(v);
        auto startVertex = GetStartVertex(v);
        if(startVertex.has_value())
            return idMap.at(startVertex.value());
        return {};
    }

    bool Searched(uint32_t v) const{
        graph.CheckVertex(v);
        return startVertexes[v] != -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const Paths& paths){
        os << "Vertex -> EdgeTo | (StartVertex, Connected component ID)" << std::endl << std::endl;
        for(uint32_t i = 0; i < paths.graph.V(); ++i){
            bool wasSearched = paths.Searched(i);
            if(!wasSearched){
                std::cout << i << ": Not searched yet" << std::endl;
                continue;
            }

            auto edgeTo = paths.edgeTo[i] == -1 ? "-" : std::to_string(paths.edgeTo[i]);
            auto startVertex = wasSearched ? std::to_string(paths.GetStartVertex(i).value()) : "-";
            auto id = wasSearched ? std::to_string(paths.GetId(i).value()) : "-";

            char buffer[128];
            snprintf(buffer, sizeof(buffer), "%d -> %s | (%s, %s)", i, edgeTo.c_str(), startVertex.c_str(), id.c_str());
            os << buffer << std::endl;
        }
        return os;
    }

};