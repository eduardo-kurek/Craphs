#pragma once

#include "edges/IEdge.h"

class WeightedEdge : public IEdge {

    double weight;

public:
    WeightedEdge(uint32_t v, uint32_t w, double weight);
    double Weight() const;

};