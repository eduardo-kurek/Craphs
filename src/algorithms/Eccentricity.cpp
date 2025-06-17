#include "algorithms/Eccentricity.h"

Eccentricity::Eccentricity(const IGraph<IEdge>& graph)
	: Paths(graph)
{
 	eccentricity = new uint32_t[graph.V()]();
	for(uint32_t i = 0; i < graph.V(); i++){
		currentStartVertex = i;
		currentMaxDistance = 0;
		Run(i);
		eccentricity[i] = currentMaxDistance;
	}
}

Eccentricity::~Eccentricity(){ delete[] eccentricity; }

void Eccentricity::Receive(uint32_t v, uint32_t w, uint32_t dist){
	if(dist > currentMaxDistance)
		currentMaxDistance = dist;
}

uint32_t Eccentricity::Get(uint32_t v) const{
	graph.CheckVertex(v);
	return eccentricity[v];
}