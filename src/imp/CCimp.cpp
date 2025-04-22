#include "imp/CCImp.h"

CCImp::CCImp(const Graph& graph) : graph(graph) {
    idTable = new uint32_t[graph.V()];
}

CCImp::~CCImp(){
    delete idTable;
    idTable = nullptr;
}

bool CCImp::Connected(uint32_t v, uint32_t w){
    graph.CheckVertex(v); graph.CheckVertex(w);
    return idTable[v] == idTable[w];
}

uint32_t CCImp::Count(){ return count; }

uint32_t CCImp::Id(uint32_t v){
    graph.CheckVertex(v);
    return idTable[v];
}