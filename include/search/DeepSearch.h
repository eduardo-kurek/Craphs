#pragma once

#include "Search.h"

class DeepSearch final : public Search {

private:
    void DeepSearchRecursive(Visitor& visitor, uint32_t v, uint32_t dist);

public:
    explicit DeepSearch(const IGraph<IEdge>& graph);
    void Run(Visitor& visitor, uint32_t s) override;

};