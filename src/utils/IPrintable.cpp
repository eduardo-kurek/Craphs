#include <iostream>
#include "utils/IPrintable.h"

void IPrintable::Print() const{
    Print(std::cout);
}

std::ostream &IPrintable::Print(std::ostream& stream) const{
    return stream;
}