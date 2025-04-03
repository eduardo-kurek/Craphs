#pragma once

#include <cstdint>
#include "Graph.h"
#include "Visitor.h"

class Search {

protected:
    const Graph& graph;

public:
    explicit Search(const Graph& graph);
    virtual ~Search() = default;
    virtual void Run(Visitor& visitor, uint32_t s) = 0;
    virtual bool HasPathTo(uint32_t v) const = 0;

};