#pragma once

#include "cc/CC.h"
#include "graphs/Graph.h"

class GraphCC final : public CC {

public:
    explicit GraphCC(const Graph* graph);
    void Run() override;

};