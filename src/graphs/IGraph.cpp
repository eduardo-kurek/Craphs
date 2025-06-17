#include "graphs/IGraph.h"
#include "edges/Edge.h"
#include "edges/WeightedEdge.h"
#include <stdexcept>
#include <string>

template <EdgeType E>
bool IGraph<E>::IsValidVertex(uint32_t v) const{ return v < vertices; }

template <EdgeType E>
uint32_t IGraph<E>::V() const{ return vertices; }

template <EdgeType E>
uint32_t IGraph<E>::E() const{ return edges; }

template <EdgeType E>
uint32_t IGraph<E>::Degree(const uint32_t v) const{
    CheckVertex(v);
    uint32_t degree = 0;
    for(auto w : graphImp->Adj(v))
        degree++;
    return degree;
}

template <EdgeType E>
uint32_t IGraph<E>::MaxDegree() const{
    uint32_t max = 0;
    for(uint32_t i = 0; i < vertices; i++){
        uint32_t aux = Degree(i);
        max = std::max(max, aux);
    }
    return max;
}

template <EdgeType E>
double IGraph<E>::AverageDegree() const{
    return 2.0 * E() / V(); 
}

template <EdgeType E>
void IGraph<E>::CheckVertex(uint32_t v) const{
    if(!IsValidVertex(v)){
        const std::string msg = "Vertex " + std::to_string(v) + " out of range";
        throw std::out_of_range(msg);
    }
}

template <EdgeType E>
const std::forward_list<E>& IGraph<E>::Adj(const uint32_t v) const{
    CheckVertex(v);
    return graphImp->Adj(v);
}

template class IGraph<Edge>;
template class IGraph<WeightedEdge>;