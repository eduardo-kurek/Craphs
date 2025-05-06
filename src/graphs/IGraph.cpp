#include "graphs/IGraph.h"
#include <stdexcept>
#include <string>

bool IGraph::IsValidVertex(uint32_t v) const{ return v < vertices; }
uint32_t IGraph::V() const{ return vertices; }
uint32_t IGraph::E() const{ return edges; }

uint32_t IGraph::Degree(const uint32_t v) const{
    CheckVertex(v);
    uint32_t degree = 0;
    for(auto w : graphImp->Adj(v))
        degree++;
    return degree;
}

uint32_t IGraph::MaxDegree() const{
    uint32_t max = 0;
    for(uint32_t i = 0; i < vertices; i++){
        uint32_t aux = Degree(i);
        max = std::max(max, aux);
    }
    return max;
}

double IGraph::AverageDegree() const{
    return 2.0 * E() / V(); 
}

void IGraph::CheckVertex(uint32_t v) const{
    if(!IsValidVertex(v)){
        const std::string msg = "Vertex " + std::to_string(v) + " out of range";
        throw std::out_of_range(msg);
    }
}

const std::forward_list<uint32_t>& IGraph::Adj(const uint32_t v) const{
    CheckVertex(v);
    return graphImp->Adj(v);
}