#include "edges/WeightedEdge.h"

WeightedEdge::WeightedEdge(uint32_t v, uint32_t w, double weight) 
    : IEdge(v, w), weight(weight) {}

double WeightedEdge::Weight() const { return weight; }