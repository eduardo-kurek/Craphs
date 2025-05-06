#pragma once

#include "graphs/imp/GraphImp.h"

class AdjacentListGraph final : public GraphImp {

private:
    std::forward_list<uint32_t>* adjList;

public:
    explicit AdjacentListGraph(uint32_t vertices);
    ~AdjacentListGraph() override;
    void AddEdge(uint32_t v, uint32_t w) override;
    const std::forward_list<uint32_t>& Adj(uint32_t v) const override;
    
};
