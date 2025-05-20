#pragma once

#include "Search.h"

class DeepSearch final : public Search {

private:
    void DeepSearchRecursive(Visitor& visitor, uint32_t v);

public:
    explicit DeepSearch(const IGraph& graph);
    void Run(Visitor& visitor, uint32_t s) override;

};