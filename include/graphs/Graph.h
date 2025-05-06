#pragma once

#include "graphs/IGraph.h"
#include <iostream>

class Graph final : public IGraph {

public:
    explicit Graph(uint32_t vertices);
    ~Graph() override;
    void AddEdge(uint32_t v, uint32_t w) override;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

};
