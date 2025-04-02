#pragma once

#include <forward_list>
#include <cstdint>

class GraphImp {

    public:
    virtual void AddEdge(uint32_t v, uint32_t w) = 0;
    virtual const std::forward_list<uint32_t>& Adj(uint32_t v) const = 0;

};