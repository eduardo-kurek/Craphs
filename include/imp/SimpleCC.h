#pragma once

// The simplest CC algorithm. Groups the vertices that have both directions connecteds.
// Used most often in non-directional Graphs.

#include "imp/CCImp.h"

class SimpleCC final : public CCImp {

public:
    explicit SimpleCC(const Graph& graph);
    bool Connected(uint32_t v, uint32_t w) override;
    uint32_t Count() override;
    uint32_t Id(uint32_t v) override;

};