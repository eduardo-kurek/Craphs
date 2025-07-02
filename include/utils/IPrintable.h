#pragma once

#include <iostream>

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual std::ostream& Print(std::ostream& os = std::cout) const{ return os; }
};