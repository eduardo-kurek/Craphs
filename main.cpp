#include <iostream>
#include "graphs/Graph.h"
#include "edges/Edge.h"
#include "searchs/BFS.h"
#include "utils/PathFinder.h"

int main(){

    Graph<Edge> g(7);

    g.AddEdge({0, 1});
    g.AddEdge({0, 3});
    g.AddEdge({1, 2});
    g.AddEdge({1, 4});
    g.AddEdge({2, 5});
    g.AddEdge({3, 4});
    g.AddEdge({3, 6});
    g.AddEdge({4, 5});


    /*
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
    g.AddEdge({5, 3}); */

    PathFinder<BFS, Edge> pathFinder(g, 0);
    auto paths = pathFinder.PathsTo(5);

    std::cout << "Paths founded: " << std::endl;
    for(auto& p : paths){
        for(auto& e : p.Vertices()){
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}


