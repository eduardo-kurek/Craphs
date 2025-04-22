#pragma once

#include "Graph.h"

class CCImp {

protected:
    uint32_t count;
    uint32_t* idTable;
    const Graph& graph;

public:
    explicit CCImp(const Graph& graph);
    virtual ~CCImp();
    virtual void Run() = 0;
    bool Connected(uint32_t v, uint32_t w);
    uint32_t Count();
    uint32_t Id(uint32_t v);

};