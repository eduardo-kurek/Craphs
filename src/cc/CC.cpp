#include "cc/CC.h"

CC::CC(const IGraph* graph) : graph(graph){
    id = new uint32_t[graph->V()];
}

CC::~CC(){
    delete[] id;
    id = nullptr;
}

uint32_t CC::Id(uint32_t v){
    graph->CheckVertex(v);
    return id[v];
}

uint32_t CC::Count(){ return count; }

bool CC::Connected(uint32_t v, uint32_t w){
    return Id(v) == Id(w);
}
