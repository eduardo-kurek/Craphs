#pragma once

#include "searchs/Search.h"
#include <queue>
#include <optional>
#include <unordered_map>

template <EdgeType E>
class BFS final : public Search<E> {
	using Adj = std::queue<E>;

	struct Context {
		Adj adj;
		uint32_t dist;
		bool* marked;

		void Pop(){ adj.pop(); }
		const E& Front() const{ return adj.front(); }
		bool IsEmpty() const{ return adj.empty(); }

		void PopUntilFrontIsValidVertex(){
			while(!IsEmpty()){
				const E& edge = Front();
				if(IsValidEdge(edge))
					return;
				Pop();
			}
		}

	private:
		bool IsValidEdge(const E& edge) const{ return !marked[edge.Other()]; }
	};

	// Given an Edge v -> w; The key is W, and the value is a vector of edges incident to W;
	using IncidentEdgesDictionary = std::unordered_map<uint32_t, std::vector<E>>;
	// Stores the IncidentEdgesDictionary for each distance;
	using DistancesDictionary = std::unordered_map<uint32_t, IncidentEdgesDictionary>;
	DistancesDictionary lookupTable;
	std::queue<Context> queue;
	E starterEdge;

protected:
	void Reset() override{
		Search<E>::Reset();
		queue = std::queue<Context>();
		lookupTable = DistancesDictionary();
	}

	void DoStart(uint32_t s) override{
		UpdateStarterEdge(s);
		PushStarterContextToQueue();
		PushStarterEdgeToLookupTable();
		this->Next();
	}

	void DoNext() override{
		EnsureQueueNotEmpty();
		auto edge = GetNextValidEdge();
		if(!edge){
			SetDone();
			return;
		}
		this->Mark((*edge).Other());
		PushNewContext(*edge);
		PushAdjacentEdgesToLookupTable(*edge);
		UpdateIteration(*edge);
	}

public:
	explicit BFS(const IGraph<E>& graph)
		: Search<E>(graph) {}

private:
	void UpdateStarterEdge(uint32_t s){ starterEdge.SetEither(-1); starterEdge.SetOther(s); }
	void PushStarterContextToQueue(){ queue.push({GetStarterAdj(), 0, this->marked});  }
	Adj GetStarterAdj() const { Adj adj; adj.push(starterEdge); return adj; }
	void PushStarterEdgeToLookupTable(){ LookupTablePush(GetCurrentDistance(), starterEdge.Other(), starterEdge); }
	void LookupTablePush(uint32_t dist, uint32_t w, const E& edge){ lookupTable[dist][w].push_back(edge); }

	void EnsureQueueNotEmpty() const{
		if(queue.empty())
			throw std::runtime_error("Trying to access invalid element");
	}

	std::optional<E> GetNextValidEdge(){
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
	E ContextEdge() const { return GetContext()->Front(); }
	const Context* GetContext() const { return &queue.front(); }
	Context* GetContext(){ return &queue.front(); }
	void ContextDelete(){ queue.pop(); }

	void PushNewContext(const E& edge){
		Adj adj = GetAdjNotMarked(edge.Other());
		queue.emplace(std::move(adj), GetNextDistance(), this->marked);
	}

	Adj GetAdjNotMarked(uint32_t v){
		Adj adj;
		for(const E& edge : this->graph.Adj(v)){
			uint32_t i = edge.Other();
			if(this->IsNotMarked(i))
				adj.push(edge);
		}
		return adj;
	}

	void PushAdjacentEdgesToLookupTable(const E& edge){
		const uint32_t dist = GetNextDistance();
		for(const E& e : this->graph.Adj(edge.Other()))
			LookupTablePush(dist, e.Other(), e);
	}

	void UpdateIteration(const E& edge){ this->current = BuildIteration(edge); }
	Iteration<E> BuildIteration(const E& edge) const{
		return { GetAlternativeEdges(edge), GetCurrentDistance(), this->GetCount() };
	}
	std::vector<E> GetAlternativeEdges(const E& edge) const{
		return lookupTable.at(GetCurrentDistance()).at(edge.Other());
	}

	uint32_t GetCurrentParent() const{ return GetContext()->parent; }
	uint32_t GetCurrentDistance() const{ return GetContext()->dist; }
	uint32_t GetNextDistance() const{ return GetCurrentDistance() + 1; }
	bool QueueNotEmpty() const{ return !queue.empty(); }
	void SetDone(){ this->isDone = true; }
};