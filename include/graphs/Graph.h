#pragma once

#include <memory>
#include "tinyxml2.h"
#include "graphs/IGraph.h"

template <EdgeType E>
class Graph final : public IGraph<E> {

    static std::unique_ptr<tinyxml2::XMLDocument> LoadGEXF(const char* filename);

public:
    explicit Graph(uint32_t vertices);
    ~Graph() override;
    void AddEdge(E&& edge) override;
    bool IsConnected(uint32_t v, uint32_t w) const override;

    friend std::ostream& operator<<(std::ostream& os, const Graph<E>& graph){
        os << "Graph(V=" << graph.vertices << ", E=" << graph.edges << ")" << std::endl;
        os << "Max degree: " << graph.MaxDegree() << std::endl;
        os << "Average degree: " << graph.AverageDegree() << std::endl;
        for(uint32_t v = 0; v < graph.V(); v++){
            for(const auto w : graph.Adj(v)){
                os << v << "-" << w << std::endl;
            }
        }
        return os;
    }

    static Graph<E> FromGEXF(const char* filename);

};
