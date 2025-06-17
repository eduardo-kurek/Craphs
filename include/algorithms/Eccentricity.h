#pragma once

#include <ostream>
#include "graphs/IGraph.h"
#include "search/BreadthFirstSearch.h"
#include "visitors/Paths.h"

class Eccentricity final : private Paths<BreadthFirstSearch> {
public:
	explicit Eccentricity(const IGraph<IEdge>& graph);
	~Eccentricity() override;
	void Receive(uint32_t v, uint32_t w, uint32_t dist) override;
	uint32_t Get(uint32_t v) const;

	friend std::ostream& operator<<(std::ostream& os, const Eccentricity& ecc){
		os << "Eccentricity of the graph:\n";
		for (uint32_t i = 0; i < ecc.graph.V(); i++) {
			os << "Vertex " << i << ": " << ecc.eccentricity[i] << "\n";
		}
		return os;
	}

private:
	uint32_t* eccentricity;
	uint32_t currentStartVertex;
	uint32_t currentMaxDistance;

};

