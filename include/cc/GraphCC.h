#pragma once

#include "cc/CC.h"
#include "graphs/Graph.h"
#include "visitors/Visitor.h"

class GraphCC final : public CC, private Visitor {

protected:
    explicit GraphCC(const Graph<IEdge>& graph);
    void Run() override;

public:
    static GraphCC Run(const Graph<IEdge>& graph){
        GraphCC cc(graph);
        cc.Run();
        return cc;
    }

    void Receive(uint32_t v, uint32_t w, uint32_t) override;

};
