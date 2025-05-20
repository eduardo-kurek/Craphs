#include "graphs/Graph.h"

#define LOG(x) std::cout << x << std::endl;

int main(){

    Graph g = Graph::FromGEXF("../LesMiserables.gexf");

    return 0;
}