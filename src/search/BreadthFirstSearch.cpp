#include "search/BreadthFirstSearch.h"

void BreadthFirstSearch::Run(Visitor &visitor, uint32_t s){
    graph.CheckVertex(s);
    Prepare(visitor, s);
    auto queue = InitQueue(s);
    
    while(!queue.empty()){
        uint32_t v = queue.front(); queue.pop();
        for(uint32_t w : graph.Adj(v)){
            if(!marked[w]){
                visitor.Receive(v, w);
                Mark(w);
                queue.push(w);
            }
        }
    }
}

void BreadthFirstSearch::Prepare(Visitor& visitor, uint32_t s){
    ClearMarkeds();
    visitor.Clear();
    visitor.Receive(-1, s);
}

std::queue<uint32_t> BreadthFirstSearch::InitQueue(uint32_t s){
    std::queue<uint32_t> queue;
    queue.push(s);
    Mark(s);
    return queue;
}
