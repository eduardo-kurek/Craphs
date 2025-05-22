#pragma once

#include <iomanip>
#include <ostream>
#include "graphs/IGraph.h"
#include "search/BreadthFirstSearch.h"
#include "visitors/Paths.h"

class ClosenessCentrality final : private Paths<BreadthFirstSearch> {
public:
    explicit ClosenessCentrality(const IGraph& graph);
    ~ClosenessCentrality() override;
    void Receive(uint32_t v, uint32_t w, uint32_t dist) override;
    float Get(uint32_t v) const;
    float GetNormalized(uint32_t v) const;

    friend std::ostream& operator<<(std::ostream& os, const ClosenessCentrality& cc){
        os << "Closeness Centrality of the graph (normalized):\n";
        for(uint32_t i = 0; i < cc.graph.V(); i++)
            os << "Vertex " << i << ": " << std::fixed << std::setprecision(4) << cc.GetNormalized(i) << "\n";
        return os;
    }

private:
    float* closenessCentrality;
    uint32_t currentStartVertex;
    uint32_t currentDistance;
};