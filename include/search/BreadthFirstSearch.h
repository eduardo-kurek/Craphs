#pragma once

#include <queue>
#include "Search.h"

class BreadthFirstSearch final : public Search {
public:
    explicit BreadthFirstSearch(const IGraph<IEdge>& graph);
    ~BreadthFirstSearch() override;
    void Run(Visitor& visitor, uint32_t s) override;

private:
    std::queue<uint32_t> queue;
    uint32_t s;
    uint32_t* distances;
    Visitor* visitor;

    void Init(Visitor& visitor, uint32_t s);
    void Clear();
    void ClearDist();
    void Execute();
    void Process(uint32_t v, uint32_t w);
    void Visit(uint32_t v, uint32_t w, uint32_t dist);
    inline bool IsNotMarked(uint32_t v) const;
    uint32_t QueuePop();


};