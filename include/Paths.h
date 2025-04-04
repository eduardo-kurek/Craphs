#pragma once

#include "Visitor.h"
#include "Search.h"
#include <cstdint>

class Paths : public Visitor {

private:
    Search& searchStrategy;
    uint32_t* edgeTo = nullptr;

public:
    explicit Paths(Search&);
    ~Paths() override;
    void Receive(uint32_t v, uint32_t w) override;
    void Print() const;

};