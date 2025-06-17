#include "algorithms/ClosenessCentrality.h"
#include <iostream>

ClosenessCentrality::ClosenessCentrality(const IGraph<IEdge>& graph)
	:Paths(graph)
{
	closenessCentrality = new float[graph.V()];
	for(uint32_t i = 0; i < graph.V(); i++){
		currentStartVertex = i;
		currentDistance = 0;
		Run(i);
		std::cout << "Current distance for " << currentStartVertex << ": " << currentDistance << std::endl;
		closenessCentrality[i] = currentDistance != 0 ? 1.0/currentDistance : 0;
	}
}

ClosenessCentrality::~ClosenessCentrality(){
	delete[] closenessCentrality;
}

void ClosenessCentrality::Receive(uint32_t v, uint32_t w, uint32_t dist){
	currentDistance += dist;
}

float ClosenessCentrality::Get(uint32_t v) const{
	this->graph.CheckVertex(v);
	return closenessCentrality[v];
}

float ClosenessCentrality::GetNormalized(uint32_t v) const{
	this->graph.CheckVertex(v);
	return closenessCentrality[v] * (graph.V() - 1);
}
