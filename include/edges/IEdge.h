#pragma once

#include <cstdint>
#include <concepts>

template<typename T>
concept EdgeType = std::derived_from<T, IEdge>;

class IEdge {

    uint32_t v, w;

protected:
    IEdge(uint32_t v, uint32_t w);

public:
    virtual ~IEdge() = default;
    uint32_t Either() const;
    uint32_t Other() const;

};