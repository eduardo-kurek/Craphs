#pragma once

#include <memory>
#include "tinyxml2.h"
#include "graphs/IGraph.h"

template <EdgeType T>
class Graph final : public IGraph<T> {

    static std::unique_ptr<tinyxml2::XMLDocument> LoadGEXF(const char* filename);

public:
    explicit Graph(uint32_t vertices);
    ~Graph() override;
    void AddEdge(T edge) override;
    bool IsConnected(uint32_t v, uint32_t w) const override;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    static Graph<T> FromGEXF(const char* filename);

};
