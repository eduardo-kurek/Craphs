#pragma once

#include <cstdint>
#include <graphs/IGraph.h>

struct Iteration {
	uint32_t w = 0;
	uint32_t v = 0;
	uint32_t dist = 0;
};

template <EdgeType E>
class Searcher {
protected:
	const IGraph<E>& graph;
	Iteration current;
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
	const Iteration& Current() const{ return current; }

	virtual void Next() = 0;


	class Iterator {
		Searcher& parent;
		bool isDone = false;

	public:
		explicit Iterator(Searcher& parent, bool isDone = false)
			: parent(parent), isDone(isDone) {}

		bool operator!=(const Iterator& other) const{
			return isDone != other.isDone || parent.Current() != other.parent.Current();
		}

		Iterator& operator++(){
			parent.Next();
			isDone = parent.IsDone();
			return *this;
		}

		Iteration operator*() const{
			return parent.Current();
		}
	};

	Iterator Begin(){ return Iterator(this); }
	Iterator End(){ return Iterator(this, false); }
};
