#pragma once

#include <cstdint>
#include <concepts>
#include "utils/IPrintable.h"

class IEdge : public IPrintable {
    uint32_t v = -1;
    uint32_t w = 0;

protected:
    IEdge(uint32_t v, uint32_t w);

public:
    IEdge() = default;
    ~IEdge() override = default;
    uint32_t Either() const;
    uint32_t Other() const;
    void SetEither(uint32_t either);
    void SetOther(uint32_t other);
    void Reverse();
    std::ostream& Print(std::ostream& os) const override;
};

template<typename E>
concept EdgeType = std::derived_from<E, IEdge> && std::default_initializable<E>;