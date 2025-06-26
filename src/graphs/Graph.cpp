#include <cstring>
#include <stdexcept>
#include "graphs/Graph.h"
#include "graphs/imp/AdjacentListGraph.h"
#include "edges/Edge.h"
#include "edges/WeightedEdge.h"

using namespace tinyxml2;

template <EdgeType E>
std::unique_ptr<XMLDocument> Graph<E>::LoadGEXF(const char* filename){
    if(filename == nullptr) throw std::invalid_argument("filename is null");
    auto doc = std::make_unique<XMLDocument>();
    if (doc->LoadFile(filename) != XML_SUCCESS) {
        const std::string filenameStr(filename);
        const std::string msg = "failed to load XML file: " + filenameStr + " -> " + doc->ErrorStr();
        throw std::invalid_argument(msg);
    }
    return doc;
}

template <EdgeType E>
Graph<E>::Graph(const uint32_t vertices)
    : IGraph<E>(vertices, new AdjacentListGraph<E>(vertices)) { }

template <EdgeType E>
Graph<E>::~Graph(){ delete this->graphImp; this->graphImp = nullptr; }

template <EdgeType E>
void Graph<E>::AddEdge(E&& edge){
    int32_t v = edge.Either(), w = edge.Other();
    if(this->IsConnected(v, w)) return;
    E reversedEdge = edge;
    reversedEdge.Reverse();
    this->graphImp->AddEdge(v, std::move(edge));
    this->graphImp->AddEdge(w, std::move(reversedEdge));
    ++this->edges;
}

template <EdgeType E>
bool Graph<E>::IsConnected(const uint32_t v, const uint32_t w) const{
    this->CheckVertex(v); this->CheckVertex(w);
    return this->graphImp->IsConnected(v, w) || this->graphImp->IsConnected(w, v);
}

template <>
Graph<Edge> Graph<Edge>::FromGEXF(const char* filename){
    auto doc = LoadGEXF(filename);
    auto root = doc->FirstChildElement("gexf");
    auto graphElement = root->FirstChildElement("graph");
    if(strcmp("undirected", graphElement->Attribute("defaultedgetype")) != 0){
        throw std::invalid_argument("Only undirected graphs are supported");
    }
    auto verticesCount = graphElement->FirstChildElement("nodes")->IntAttribute("count");

    Graph<Edge> graph(verticesCount);

    auto edgesElement = graphElement->FirstChildElement("edges");

    for(auto edge = edgesElement->FirstChildElement("edge"); edge != nullptr; edge = edge->NextSiblingElement("edge")){
        auto source = edge->IntAttribute("source");
        auto target = edge->IntAttribute("target");
        graph.AddEdge({static_cast<uint32_t>(source), static_cast<uint32_t>(target)});
    }

    return graph;
}

template class Graph<Edge>;
template class Graph<WeightedEdge>;