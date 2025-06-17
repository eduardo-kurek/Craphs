#pragma once

#include <ostream>
#include "graphs/IGraph.h"

class CC {

protected:
    uint32_t* id;
    uint32_t count = 0;
    const IGraph<IEdge>& graph;
    virtual void Run() = 0;

public:
    explicit CC(const IGraph<IEdge>& graph);
    virtual ~CC();
    uint32_t Count() const;
    uint32_t Id(uint32_t v) const;
    bool Connected(uint32_t v, uint32_t w) const;

    friend std::ostream& operator<<(std::ostream& os, const CC& graph);

};
