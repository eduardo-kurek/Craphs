#pragma once

#include <cstdint>

class Visitor {

public:
    virtual ~Visitor() = default;

    /**
     * @brief Clears the visitor state, called before each Search::Run.
     */
    virtual void Clear(){};

    /**
     * @brief When a vertex is visited, this method is called.
     * @param v The previous vertex.
     * @param w The current vertex.
     * @param dist The distance from the start vertex to the current vertex.
     */
    virtual void Receive(uint32_t v, uint32_t w, uint32_t dist)  = 0;

};