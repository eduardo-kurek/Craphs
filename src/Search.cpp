#include "Search.h"

Search::Search(const Graph& graph) : graph(graph){ }

const Graph& Search::GetGraph() const { return graph; }