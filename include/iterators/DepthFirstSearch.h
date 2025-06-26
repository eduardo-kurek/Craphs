#pragma once

#include <algorithm>
#include <stack>
#include "graphs/IGraph.h"
#include "iterators/Searcher.h"

template <EdgeType E>
class DeepFirstSearch : public Searcher<E> {
	std::stack<Iteration> stack;
	bool* marked;

protected:
	void DoStart(uint32_t v) override{

	}

	void Reset() override{
		stack = std::stack<Iteration>();
		std::fill(marked, marked + graph.V(), false);
	}

public:
	explicit DeepFirstSearch(const IGraph<E>& graph) : Searcher<E>(graph) {
		marked = new bool[graph.V()];
	}

	~DeepFirstSearch() override{ delete[] marked; marked = nullptr; }

	void Next() override{

	}
};