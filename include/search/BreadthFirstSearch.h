#pragma once

#include "Search.h"
#include <queue>

class BreadthFirstSearch final : public Search {
public:
    explicit BreadthFirstSearch(const IGraph& graph) : Search(graph) {}
    void Run(Visitor& visitor, uint32_t s) override;

private:
    void Prepare(Visitor& visitor, uint32_t s);
    std::queue<uint32_t> InitQueue(uint32_t);
};