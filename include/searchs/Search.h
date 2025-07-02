#pragma once

#include <cstdint>
#include <graphs/IGraph.h>
#include <vector>
#include <searchs/BFS.h>

template <EdgeType E>
struct Iteration {
	std::vector<E> incidentEdges;
	uint32_t distance = 0;
	uint32_t count;

	std::vector<uint32_t> Parents() const{
		std::vector<uint32_t> parents;
		parents.reserve(incidentEdges.size());
		for(const auto& edge : incidentEdges)
			parents.push_back(edge->Either());
		return parents;
	}

	uint32_t FirstParent() const{ return incidentEdges[0].Either(); }
	uint32_t Current() const{ return incidentEdges[0].Other(); }
	uint32_t Dist() const{ return distance; }
	const std::vector<E>& Edges() { return incidentEdges; }
};

template <EdgeType E>
class Search {
protected:
	const IGraph<E>& graph;
	Iteration<E> current;
	bool* marked;
	bool isDone;
	uint32_t count = 0;

	virtual void DoStart(uint32_t s) = 0;
	virtual void DoNext() = 0;
	bool IsMarked(uint32_t v) const{ return marked[v]; }
	bool IsNotMarked(uint32_t v) const { return !marked[v]; }
	void Mark(uint32_t v){ marked[v] = true; }

	void ClearMarked(){
		std::fill(marked, marked + this->graph.V(), false);
	}

	virtual void Reset(){
		isDone = false;
		count = 0;
		ClearMarked();
	}

	void IncreaseCount(){ count++; }
	uint32_t GetCount() const{ return count; }

public:
	using EdgeValue = E;

	explicit Search(const IGraph<E>& graph)
		: graph(graph), current({}), isDone(false){
		marked = new bool[graph.V()];
	}

	Search(const Search& other) = delete;
	Search& operator=(const Search& other) = delete;

	virtual ~Search(){
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
	virtual void Next(){
		IncreaseCount();
		DoNext();
	}
	uint32_t V() const { return graph->V(); }
};

template <typename S>
concept SearcherType = requires {
	typename S::EdgeValue;
	requires std::constructible_from<S, const IGraph<typename S::EdgeValue>&>;
} && std::derived_from<S, Search<typename S::EdgeValue>>;

