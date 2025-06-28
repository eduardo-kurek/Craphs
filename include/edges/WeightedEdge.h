#pragma once

#include "edges/IEdge.h"

class WeightedEdge final : public IEdge {
    double weight = 0;

public:
    WeightedEdge() = default;
    WeightedEdge(uint32_t w, uint32_t v, double weight);
    double Weight() const;
};