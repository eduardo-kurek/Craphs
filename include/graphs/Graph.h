#pragma once

#include <memory>
#include "tinyxml2.h"
#include "graphs/IGraph.h"
#include <iostream>

template <EdgeType E>
class Graph final : public IGraph<E> {

    static std::unique_ptr<tinyxml2::XMLDocument> LoadGEXF(const char* filename);

public:
    explicit Graph(uint32_t vertices);
    ~Graph() override;
    void AddEdge(E&& edge) override;
    bool IsConnected(uint32_t v, uint32_t w) const override;
    static Graph<E> FromGEXF(const char* filename);

};
