#include "edges/IEdge.h"

IEdge::IEdge(uint32_t v, uint32_t w) : v(v), w(w) {}

uint32_t IEdge::Either() const { return v; }
uint32_t IEdge::Other() const { return w; }

IEdge::~IEdge() = default;