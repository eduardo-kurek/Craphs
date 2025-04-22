#pragma once

// ConnectedComponents

#include "Graph.h"
#include "imp/CCImp.h"
#include <concepts>

template <class I>
requires std::derived_from<I, CCImp>
class CC {

protected:
    I* ccImp;

public:
    CC(const Graph& graph){
        ccImp = new I(graph);
    }

    ~CC(){
        delete ccImp;
        ccImp = nullptr;
    }

    bool Connected(uint32_t v, uint32_t w){
        return ccImp->Connected(v, w);
    }

    uint32_t Count(){
        return ccImp->Count(v, w);
    }

    uint32_t Id(uint32_t v){
        return ccImp->Id(v);
    }

};