#include "Digraph.h"

Digraph::Digraph(uint32_t vertices) : Graph(vertices){}

void Digraph::AddEdge(uint32_t v, uint32_t w){
    CheckVertex(v); CheckVertex(w);
    graphImp->AddEdge(v, w);
    edges++;
}