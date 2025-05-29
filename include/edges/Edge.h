#pragma once

#include "edges/IEdge.h"

class Edge : public IEdge {
public:
    Edge(uint32_t v, uint32_t w) : IEdge(v, w) {}
};