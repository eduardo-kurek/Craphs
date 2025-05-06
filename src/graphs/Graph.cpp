#include "graphs/Graph.h"
#include "graphs/imp/AdjacentListGraph.h"

Graph::Graph(const uint32_t vertices)
    : IGraph(vertices, new AdjacentListGraph(vertices)) { }

Graph::~Graph(){ delete graphImp; graphImp = nullptr; }

void Graph::AddEdge(const uint32_t v, const uint32_t w){
    CheckVertex(v); CheckVertex(w);
    graphImp->AddEdge(v, w);
    graphImp->AddEdge(w, v);
    edges++;
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