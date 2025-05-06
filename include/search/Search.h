#pragma once

#include <cstdint>
#include "graphs/Graph.h"
#include "visitors/Visitor.h"

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
    bool HasPathTo(uint32_t v) const;

};