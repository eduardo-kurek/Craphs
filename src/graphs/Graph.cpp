#include "graphs/Graph.h"
#include <stdexcept>
#include "graphs/imp/AdjacentListGraph.h"
#include <cstring>

using namespace tinyxml2;

template <EdgeType T>
std::unique_ptr<XMLDocument> Graph<T>::LoadGEXF(const char* filename){
    if(filename == nullptr) throw std::invalid_argument("filename is null");
    auto doc = std::make_unique<XMLDocument>();
    if (doc->LoadFile(filename) != XML_SUCCESS) {
        const std::string filenameStr(filename);
        const std::string msg = "failed to load XML file: " + filenameStr + " -> " + doc->ErrorStr();
        throw std::invalid_argument(msg);
    }
    return doc;
}

template <EdgeType T>
Graph<T>::Graph(const uint32_t vertices)
    : IGraph(vertices, new AdjacentListGraph(vertices)) { }

template <EdgeType T>
Graph<T>::~Graph(){ delete graphImp; graphImp = nullptr; }

template <EdgeType T>
void Graph<T>::AddEdge(T edge){
    uint32_t v = edge.Either(), w = edge.Other();
    if(this->IsConnected(v, w)) return;
    graphImp->AddEdge(v, edge);
    graphImp->AddEdge(w, edge);
    edges++;
}

template <EdgeType T>
bool Graph<T>::IsConnected(const uint32_t v, const uint32_t w) const{
    CheckVertex(v); CheckVertex(w);
    return graphImp->IsConnected(v, w) || graphImp->IsConnected(w, v);
}

template <EdgeType T>
Graph<T> Graph<T>::FromGEXF(const char* filename){
    auto doc = LoadGEXF(filename);
    auto root = doc->FirstChildElement("gexf");
    auto graphElement = root->FirstChildElement("graph");
    if(strcmp("undirected", graphElement->Attribute("defaultedgetype")) != 0){
        throw std::invalid_argument("Only undirected graphs are supported");
    }
    auto verticesCount = graphElement->FirstChildElement("nodes")->IntAttribute("count");

    Graph<T> graph(verticesCount);

    auto edgesElement = graphElement->FirstChildElement("edges");

    for(auto edge = edgesElement->FirstChildElement("edge"); edge != nullptr; edge = edge->NextSiblingElement("edge")){
        auto source = edge->IntAttribute("source");
        auto target = edge->IntAttribute("target");
        graph.AddEdge(source, target);
    }

    return graph;
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
