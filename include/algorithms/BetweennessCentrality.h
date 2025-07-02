#pragma once

#include <iomanip>

#include "graphs/Graph.h"
#include "graphs/IGraph.h"
#include "searchs/BFS.h"
#include <stack>

#include "utils/PathFinder.h"

template <EdgeType E>
class BetweennessCentrality final {
	const IGraph<E>& graph;
	double* centrality;

	void AllocMembers(){
		centrality = new double[graph.V()];
		std::fill(centrality, centrality + graph.V(), 0.0);
	}

	void Compute(){
		for(uint32_t s = 0; s < graph.V(); s++)
			ComputeVertice(s);
	}

	void ComputeVertice(uint32_t s){
		const PathFinder<BFS, E> finder(graph, s);
		for(uint32_t target = 0; target < graph.V(); target++)
			ComputeTarget(finder, target);
	}

	void ComputeTarget(const PathFinder<BFS, E>& finder, uint32_t target){
		if(TargetIsSameAsSource(finder, target)) return;
		ComputeAllPathsOfTarget(finder, target);
	}

	static bool TargetIsSameAsSource(const PathFinder<BFS, E>& finder, uint32_t target){
		return target == finder.Source();
	}

	void ComputeAllPathsOfTarget(const PathFinder<BFS, E>& finder, uint32_t target){
		auto allValidPaths = finder.PathsTo(target);
		uint32_t qtPaths = allValidPaths.size();
		for(auto path : allValidPaths)
			AddPathContribution(path, qtPaths);
	}

	void AddPathContribution(typename PathFinder<BFS, E>::Path path, uint32_t qtPaths){
		const double contribution = CalculateIndividualContribution(qtPaths);
		const std::vector<uint32_t> vertices = path.Vertices();
		for(uint32_t i = 1; i < vertices.size()-1; i++){
			const uint32_t current = vertices[i];
			centrality[current] += contribution;
		}
	}

	static double CalculateIndividualContribution(uint32_t qtPaths){ return 1.0 / qtPaths; }

	void Normalize(){
		for(uint32_t v = 0; v < graph.V(); v++)
			centrality[v] /= 2.0;
	}

public:
	explicit BetweennessCentrality(const Graph<E>& graph) : graph(graph){
		AllocMembers();
		Compute();
		Normalize();
	}

	~BetweennessCentrality(){ delete[] centrality; }

	double Get(uint32_t v) const{
		graph.CheckVertex(v);
		return centrality[v];
	}

	std::ostream& Print(std::ostream& os) const{
		os << "Betweenness Centrality:\n";
		os << std::fixed << std::setprecision(5);
		for(uint32_t v = 0; v < graph.V(); v++){
			os << "Vertex " << v << ": " << centrality[v] << "\n";
		}
		return os;
	}
};
