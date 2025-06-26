#include <iostream>
#include "graphs/Graph.h"
#include "edges/Edge.h"
#include "iterators/DepthFirstSearch.h"

int main(){

    //Graph<Edge> g = Graph<Edge>::FromGEXF("../LesMiserables.gexf");

    Graph<Edge> g(13);

    g.AddEdge({0, 5});
    g.AddEdge({4, 3});
    g.AddEdge({0, 1});
    g.AddEdge({9, 12});
    g.AddEdge({6, 4});
    g.AddEdge({5, 4});
    g.AddEdge({0, 2});
    g.AddEdge({11, 12});
    g.AddEdge({9, 10});
    g.AddEdge({0, 6});
    g.AddEdge({7, 8});
    g.AddEdge({9, 11});
    g.AddEdge({5, 3});

    g.Print(std::cout);
    std::cout << std::endl;

    DepthFirstSearch dfs(g);

    for(dfs.Start(0); !dfs.IsDone(); dfs.Next()){
        const auto& [w, v, dist] = dfs.Current();
        std::cout << "w: " << w << ", v: " << v << ", dist: " << dist << std::endl;
    }

    return 0;
}