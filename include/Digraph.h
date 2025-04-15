#pragma once

#include "Graph.h"

class Digraph : public Graph {

public:
    explicit Digraph(uint32_t vertices);
    virtual void AddEdge(uint32_t v, uint32_t w) override;

};