#pragma once

#include <cstdint>
#include <concepts>
#include "utils/IPrintable.h"

class IEdge : public IPrintable {

    uint32_t v, w;

protected:
    IEdge(uint32_t v, uint32_t w);

public:
    ~IEdge() override = default;
    uint32_t Either() const;
    uint32_t Other() const;
    void Reverse();
    std::ostream& Print(std::ostream& os) const override;

};

template<typename E>
concept EdgeType = std::derived_from<E, IEdge>;