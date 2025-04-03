#include "Graph.h"
#include <string>

bool Graph::IsValidVertex(uint32_t v) const{
    return v < vertices;
}

void Graph::CheckVertex(uint32_t v) const{
    if(!IsValidVertex(v)){
        const std::string msg = "Vertex " + std::to_string(v) + " out of range";
        throw std::out_of_range(msg);
    }
}

Graph::Graph(const uint32_t vertices) : vertices(vertices), edges(0){
    graphImp = new AdjacentListGraph(vertices);
}

Graph::~Graph(){ delete graphImp; graphImp = nullptr; }
uint32_t Graph::V() const{ return vertices; }
uint32_t Graph::E() const{ return edges; }

void Graph::AddEdge(const uint32_t v, const uint32_t w){
    CheckVertex(v); CheckVertex(w);
    graphImp->AddEdge(v, w);
    graphImp->AddEdge(w, v);
    edges++;
}

uint32_t Graph::Degree(const uint32_t v) const{
    CheckVertex(v);
    uint32_t degree = 0;
    for(auto w : graphImp->Adj(v))
        degree++;
    return degree;
}

uint32_t Graph::MaxDegree() const{
    uint32_t max = 0;
    for(uint32_t i = 0; i < vertices; i++){
        uint32_t aux = Degree(i);
        max = std::max(max, aux);
    }
    return max;
}

double Graph::AverageDegree() const{
    return 2.0 * E() / V(); 
}

const std::forward_list<uint32_t>& Graph::Adj(const uint32_t v) const{
    CheckVertex(v);
    return graphImp->Adj(v);
}

std::ostream& operator<<(std::ostream& os, const Graph& graph){
    os << "Graph(V=" << graph.vertices << ", E=" << graph.edges << ")" << std::endl;
    os << "Max degree: " << graph.MaxDegree() << std::endl;
    os << "Average degree: " << graph.AverageDegree() << std::endl;
    for(uint32_t v = 0; v < graph.V(); v++){
        for(const auto w : graph.Adj(v)){
            os << v << "-" << w << std::endl;
        }
    }
    return os;
}