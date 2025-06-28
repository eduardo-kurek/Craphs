#pragma once

#include "iterators/Searcher.h"
#include <queue>
#include <optional>

template <EdgeType E>
class BreadthFirstSearcher final : public Searcher<E> {
	using Adj = std::queue<const E*>;

	struct Context {
		Adj adj;
		uint32_t dist;
		bool* marked;

		void Pop(){ adj.pop(); }
		const E* Front() const{ return adj.front(); }
		bool IsEmpty() const{ return adj.empty(); }

		void PopUntilFrontIsValidVertex(){
			while(!IsEmpty()){
				const E* edge = Front();
				if(IsValidEdge(edge))
					return;
				Pop();
			}
		}

	private:
		bool IsValidEdge(const E* edge) const{ return !marked[edge->Other()]; }
	};

	std::queue<Context> queue;
	E starter;

	std::optional<const E*> GetNextValidEdge(){
		while(QueueNotEmpty()){
			ContextPrepare();
			if(ContextIsNotEmpty())
				return ContextEdge();
			ContextDelete();
		}
		return {};
	}

	void ContextPrepare(){ GetContext()->PopUntilFrontIsValidVertex(); }
	bool ContextIsNotEmpty() const { return !GetContext()->IsEmpty(); }
	const E* ContextEdge() const { return GetContext()->Front(); }
	const Context* GetContext() const { return &queue.front(); }
	Context* GetContext(){ return &queue.front(); }
	void ContextDelete(){ queue.pop(); }

	void UpdateIteration(const E* edge){ this->current = BuildIteration(edge); }
	Iteration<E> BuildIteration(const E* edge) const{ return { edge, GetCurrentDistance() }; }
	uint32_t GetCurrentParent() const{ return GetContext()->parent; }
	uint32_t GetCurrentDistance() const{ return GetContext()->dist; }

	void PushNewContext(const E* edge){
		Adj adj = GetAdj(edge->Other());
		Context ctx = {adj, GetNextDistance(), this->marked};
		queue.push(ctx);
	}

	Adj GetAdj(uint32_t v){
		Adj adj;
		for(const E& edge : this->graph.Adj(v)){
			uint32_t i = edge.Other();
			if(this->IsNotMarked(i))
				adj.push(&edge);
		}
		return adj;
	}

	void EnsureQueueNotEmpty() const{
		if(queue.empty())
			throw std::runtime_error("Trying to access invalid element");
	}

	uint32_t GetNextDistance() const{ return GetCurrentDistance() + 1; }
	bool QueueNotEmpty() const{ return !queue.empty(); }
	void SetDone(){ this->isDone = true; }

protected:
	void DoStart(uint32_t s) override{
		starter.SetEither(-1);
		starter.SetOther(s);
		Adj adj; // fila
		adj.push(&starter);
		Context ctx = {adj, 0, this->marked};
		queue.push(ctx);
		Next();
	}

	void Reset() override{
		Searcher<E>::Reset();
		queue = std::queue<Context>();
	}

public:
	explicit BreadthFirstSearcher(const IGraph<E>& graph)
		: Searcher<E>(graph) {}


	void Next() override{
		EnsureQueueNotEmpty();
		auto edge = GetNextValidEdge();
		if(!edge){
			SetDone();
			return;
		}
		this->Mark(edge.value()->Other());
		PushNewContext(*edge);
		UpdateIteration(*edge);
	}

};