#include <iostream>
#include "graphs/Graph.h"
#include "edges/Edge.h"
#include "iterators/BreadthFirstSearcher.h"

int main(){

    //Graph<Edge> g = Graph<Edge>::FromGEXF("../LesMiserables.gexf");

    Graph<Edge> g(7);

    g.AddEdge({0, 1});
    g.AddEdge({0, 3});
    g.AddEdge({1, 2});
    g.AddEdge({1, 4});
    g.AddEdge({2, 5});
    g.AddEdge({3, 4});
    g.AddEdge({3, 6});
    g.AddEdge({4, 5});

    // g.AddEdge({0, 5});
    // g.AddEdge({4, 3});
    // g.AddEdge({0, 1});
    // g.AddEdge({9, 12});
    // g.AddEdge({6, 4});
    // g.AddEdge({5, 4});
    // g.AddEdge({0, 2});
    // g.AddEdge({11, 12});
    // g.AddEdge({9, 10});
    // g.AddEdge({0, 6});
    // g.AddEdge({7, 8});
    // g.AddEdge({9, 11});
    // g.AddEdge({5, 3});

    g.Print(std::cout);
    std::cout << std::endl;

    BreadthFirstSearcher dfs(g);

    for(dfs.Start(0); !dfs.IsDone(); dfs.Next()){
        auto i = dfs.Current();
        std::string parents;
        for(auto parent : i.Parents()){
            parents += std::to_string(parent) + " ";
        }
        std::cout << "v: " << parents << ", w: " << i.Current() << ", dist: " << i.Dist() << std::endl;
    }

    return 0;
}

