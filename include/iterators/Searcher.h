#pragma once

#include <cstdint>
#include <graphs/IGraph.h>
#include <vector>

template <EdgeType E>
struct Iteration {
	std::vector<const E*> incidentEdges;
	uint32_t distance = 0;

	std::vector<uint32_t> Parents() const{
		std::vector<uint32_t> parents;
		parents.reserve(incidentEdges.size());
		for(const auto& edge : incidentEdges)
			parents.push_back(edge->Either());
		return parents;
	}

	uint32_t FirstParent() const{ return incidentEdges[0]->Either(); }
	uint32_t Current() const{ return incidentEdges[0]->Other(); }
	uint32_t Dist() const{ return distance; }
};

template <EdgeType E>
class Searcher {
protected:
	const IGraph<E>& graph;
	Iteration<E> current;
	bool* marked;
	bool isDone;

	virtual void DoStart(uint32_t s) = 0;
	bool IsMarked(uint32_t v) const{ return marked[v]; }
	bool IsNotMarked(uint32_t v) const { return !marked[v]; }
	void Mark(uint32_t v){ marked[v] = true; }

	void ClearMarked(){
		std::fill(marked, marked + this->graph.V(), false);
	}

	virtual void Reset(){
		isDone = false;
		ClearMarked();
	}

public:
	explicit Searcher(const IGraph<E>& graph)
		: graph(graph), current({}), isDone(false){
		marked = new bool[graph.V()];
	}

	virtual ~Searcher(){
		delete[] marked;
		marked = nullptr;
	}

	void Start(uint32_t s){
		graph.CheckVertex(s);
		Reset();
		DoStart(s);
	}

	bool IsDone() const{ return isDone; }
	const Iteration<E>& Current() const{ return current; }
	virtual void Next() = 0;
};
