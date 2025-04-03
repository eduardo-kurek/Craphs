#pragma once

#include "Graph.h"
#include "Visitor.h"
#include <cstdint>

class Paths : public Visitor {

private:
    const Graph& graph;
    uint32_t* edgeTo = nullptr;

public:
    explicit Paths(const Graph&);
    ~Paths() override;
    void Receive(uint32_t v, uint32_t w) override;
    void Print() const;

};