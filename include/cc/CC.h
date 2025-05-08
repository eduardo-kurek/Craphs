#pragma once

#include "graphs/IGraph.h"

class CC {

protected:
    uint32_t* id;
    uint32_t count = 0;
    const IGraph* graph;

public:
    explicit CC(const IGraph* graph);
    virtual ~CC();
    virtual void Run() = 0;
    uint32_t Count();
    uint32_t Id(uint32_t v);
    bool Connected(uint32_t v, uint32_t w);

};