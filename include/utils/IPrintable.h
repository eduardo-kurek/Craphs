#pragma once

#include <ostream>

class IPrintable {
public:
    virtual void Print() const;
    virtual std::ostream& Print(std::ostream& stream) const;
};