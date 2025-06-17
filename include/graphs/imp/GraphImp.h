#pragma once

#include <cstdint>
#include <forward_list>
#include "edges/IEdge.h"

template <EdgeType E>
class GraphImp {

public:
	virtual ~GraphImp() = default;
	virtual void AddEdge(uint32_t v, E&& edge) = 0;
	virtual bool IsConnected(uint32_t v, uint32_t w) const = 0;
	virtual const std::forward_list<E>& Adj(uint32_t v) const = 0;

};