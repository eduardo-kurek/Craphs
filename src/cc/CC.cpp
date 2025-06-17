#include "cc/CC.h"

CC::CC(const IGraph<IEdge>& graph) : graph(graph){
    id = new uint32_t[graph.V()];
}

CC::~CC(){
    delete[] id;
    id = nullptr;
}

uint32_t CC::Id(uint32_t v) const{
    graph.CheckVertex(v);
    return id[v];
}

uint32_t CC::Count() const{ return count; }

bool CC::Connected(uint32_t v, uint32_t w) const{
    return Id(v) == Id(w);
}


std::ostream& operator<<(std::ostream& os, const CC& cc){
    os << "CC(count=" << cc.Count() << ")" << std::endl;
    os << "Vertex: Id" << std::endl;
    for(uint32_t v = 0; v < cc.graph.V(); v++){
        os << v << ": " << cc.Id(v) << std::endl;
    }
    return os;
}