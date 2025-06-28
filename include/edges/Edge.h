#pragma once

#include "edges/IEdge.h"

class Edge final : public IEdge {
public:
    Edge() = default;
    Edge(uint32_t v, uint32_t w) : IEdge(v, w) {}
};