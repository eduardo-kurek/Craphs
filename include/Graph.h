#pragma once

#include <cstdint>
#include <iostream>
#include "imp/GraphImp.h"
#include "imp/AdjacentListGraph.h"

class Graph {

protected:
    const uint32_t vertices;
    uint32_t edges;
    GraphImp* graphImp;
    bool IsValidVertex(uint32_t v) const;

public:
    explicit Graph(uint32_t vertices);
    virtual ~Graph();
    uint32_t V() const;
    uint32_t E() const;
    virtual void AddEdge(uint32_t v, uint32_t w);
    uint32_t Degree(uint32_t v) const;
    uint32_t MaxDegree() const;
    double AverageDegree() const;
    void CheckVertex(uint32_t v) const;
    const std::forward_list<uint32_t>& Adj(uint32_t v) const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

};
