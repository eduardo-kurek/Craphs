#pragma once

#include <stack>
#include <queue>
#include "include/graphs/IGraph.h"
#include "include/iterators/Searcher.h"

#define END_OF_ITERATION (-1)

template <EdgeType E>
class DepthFirstSearch final : public Searcher<E> {
	using Adj = std::queue<uint32_t>;
	struct Context {
		uint32_t w{};
		uint32_t v{};
		Adj adj;
		const bool* marked;

		uint32_t Front() const{ return adj.front(); }
		void Pop() { adj.pop(); }
		bool IsEmpty() const{ return adj.empty();}
		void Delete(std::stack<Context>& stack) { stack.pop(); }

		void PopUntilFrontIsValidVertex(){
			while(!IsEmpty()){
				uint32_t nextVertex = Front();
				if(IsValidVertex(nextVertex))
					return;
				Pop();
			}
		}

	private:
		bool IsValidVertex(uint32_t v) const{ return !marked[v]; }
	};

	std::stack<Context> stack;

	uint32_t StackPop(){
		while(!StackIsEmpty()){
			uint32_t v = GetNextVertex();
			if(ReachedEndOfIteration(v))
				return END_OF_ITERATION;
			return v;
		}
		return END_OF_ITERATION;
	}

	uint32_t GetNextVertex(){
		Context* ctx = GetNextValidContext();
		if(ctx == nullptr) return -1;
		const uint32_t v = ctx->Front(); ctx->Pop();
		return v;
	}

	Context* GetNextValidContext(){
		while(StackNotEmpty()){
			Context* ctx = GetContext();
			ctx->PopUntilFrontIsValidVertex();
			if(!ctx->IsEmpty())
				return ctx;
			ctx->Delete(stack);
		}
		return nullptr;
	}

	void StackPush(uint32_t w, uint32_t v){
		Adj adj = GetAdj(v);
		stack.push({w, v, adj, this->marked});
	}

	Context* GetContext(){ return stack.empty() ? nullptr : &stack.top(); }

	Adj GetAdj(uint32_t v){
		Adj adj;
		for(E edge : this->graph.Adj(v)){
			uint32_t i = edge.Other();
			if(this->IsNotMarked(i))
				adj.emplace(i);
		}
		return adj;
	}

	bool StackIsEmpty() const{ return stack.empty(); }
	bool StackNotEmpty() const{ return !stack.empty(); }

	void EnsureStackNotEmpty() const {
		if(StackIsEmpty())
			throw std::runtime_error("Trying to access invalid element");
	}

	static bool ReachedEndOfIteration(uint32_t v){
		return v == END_OF_ITERATION;
	}

	void SetDone(){ this->isDone = true; }

	void ProcessVertex(uint32_t w, uint32_t v){
		this->Mark(v);
		StackPush(w, v);
		UpdateCurrent();
	}

	void UpdateCurrent(){
		Context* ctx = GetContext();
		this->current = {ctx->w, ctx->v, static_cast<uint32_t>(stack.size()-1)};
	}

protected:
	void DoStart(uint32_t s) override{
		ProcessVertex(-1, s);
	}

	void Reset() override{
		Searcher<E>::Reset();
		stack = std::stack<Context>();
	}

public:
	explicit DepthFirstSearch(const IGraph<E>& graph)
		: Searcher<E>(graph) {}

	void Next() override{
		EnsureStackNotEmpty();
		const uint32_t v = StackPop();
		if(ReachedEndOfIteration(v))
			SetDone();
		else{
			const uint32_t previous = GetContext()->v;
			ProcessVertex(previous, v);
		}
	}
};