#pragma once

#include "Search.h"

class DeepSearch final : public Search {

private:
    bool* marked = nullptr;
    void DeepSearchRecursive(Visitor& visitor, uint32_t v);
    void ClearMarkeds();

public:
    explicit DeepSearch(const Graph& graph);
    ~DeepSearch() override;
    void Run(Visitor& visitor, uint32_t s) override;
    bool HasPathTo(uint32_t v) const override;

};