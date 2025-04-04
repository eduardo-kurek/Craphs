#pragma once

#include "Visitor.h"
#include "Search.h"
#include <cstdint>
#include <vector>
#include <stack>

class Paths : public Visitor {

private:
    Search& searchStrategy;
    const uint32_t startVertex = 0;
    uint32_t* edgeTo = nullptr;
    std::stack<uint32_t> GetPathStack(uint32_t);
    std::vector<uint32_t> GetPathVector(std::stack<uint32_t>&);

public:
    Paths(Search&, uint32_t startVertex = 0);
    ~Paths() override;
    void Receive(uint32_t v, uint32_t w) override;
    std::vector<uint32_t> PathTo(uint32_t);
    void Print() const;

};