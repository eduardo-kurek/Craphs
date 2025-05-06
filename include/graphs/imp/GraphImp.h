#pragma once

#include <cstdint>
#include <forward_list>

class GraphImp {

public:
	virtual ~GraphImp() = default;
	virtual void AddEdge(uint32_t v, uint32_t w) = 0;
	virtual const std::forward_list<uint32_t>& Adj(uint32_t v) const = 0;

};