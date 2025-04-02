#pragma once

#include "imp/GraphImp.h"
#include <forward_list>

class AdjacentListGraph : public GraphImp {

private:
    std::forward_list<uint32_t>* adjList;

public:
    AdjacentListGraph(uint32_t vertices);
    ~AdjacentListGraph();
    void AddEdge(uint32_t v, uint32_t w) override;
    const std::forward_list<uint32_t>& Adj(uint32_t v) const override;
    
};
