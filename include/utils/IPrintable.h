#pragma once

#include <ostream>

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void Print() const;
    virtual std::ostream& Print(std::ostream& os) const;
};