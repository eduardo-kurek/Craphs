#include "cc/GraphCC.h"
#include <iostream>
#include "search/DeepSearch.h"
#include "visitors/Paths.h"

GraphCC::GraphCC(const Graph<IEdge>& graph) : CC(graph) { }

void GraphCC::Run(){
    DeepSearch searcher(graph);
    for(int i = 0; i < graph.V(); i++){
        if(searcher.IsMarked(i)) continue;
        searcher.Run(*this, i);
        count++;
    }
}

void GraphCC::Receive(uint32_t v, uint32_t w, uint32_t){
    id[w] = count;
}
