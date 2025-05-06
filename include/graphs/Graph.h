#pragma once

#include <iostream>
#include "graphs/IGraph.h"

class Graph final : public IGraph {

public:
    explicit Graph(uint32_t vertices);
    ~Graph() override;
    void AddEdge(uint32_t v, uint32_t w) override;
    bool IsConnected(uint32_t v, uint32_t w) const override;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

};
