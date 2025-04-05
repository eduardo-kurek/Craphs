#pragma once

#include "Graph.h"
#include "Visitor.h"
#include <cstdint>

class Search {

protected:
    bool* marked = nullptr;
    const Graph& graph;
    void ClearMarkeds();
    void Mark(uint32_t v);

public:
    explicit Search(const Graph& graph);
    virtual ~Search();
    virtual void Run(Visitor& visitor, uint32_t s) = 0;
    bool HasPathTo(const uint32_t v) const;

};