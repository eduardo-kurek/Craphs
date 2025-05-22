#include "search/BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(const IGraph& graph) : Search(graph){
    distances = new uint32_t[graph.V()]();
}

BreadthFirstSearch::~BreadthFirstSearch(){
    delete[] distances;
}

void BreadthFirstSearch::Run(Visitor& visitor, uint32_t s){
    Init(visitor, s);
    Clear();
    Execute();
}

void BreadthFirstSearch::Clear(){
    ClearMarkeds();
    ClearDist();
    visitor->Clear();
    queue = std::queue<uint32_t>();
}

void BreadthFirstSearch::ClearDist(){
    for(uint32_t i = 0; i < graph.V(); i++)
        distances[i] = -1;
}

void BreadthFirstSearch::Init(Visitor& visitor, uint32_t s){
    graph.CheckVertex(s);
    this->visitor = &visitor;
    this->s = s;
}

void BreadthFirstSearch::Execute(){
    Visit(-1, s, 0);

    while(!queue.empty()){
        const uint32_t v = QueuePop();
        for(const uint32_t w : graph.Adj(v))
            Process(v, w);
    }
}

void BreadthFirstSearch::Process(uint32_t v, uint32_t w){
    if(IsNotMarked(w))
        Visit(v, w, distances[v]+1);
}

void BreadthFirstSearch::Visit(uint32_t v, uint32_t w, uint32_t dist){
    visitor->Receive(v, w, dist);
    marked[w] = true;
    distances[w] = dist;
    queue.push(w);
}

inline bool BreadthFirstSearch::IsNotMarked(uint32_t v) const{ return !marked[v]; }

uint32_t BreadthFirstSearch::QueuePop(){
    const uint32_t entry = queue.front();
    queue.pop();
    return entry;
}
