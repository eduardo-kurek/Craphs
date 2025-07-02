#pragma once

#include <unordered_set>

#include "searchs/Search.h"
#include "forward_list"



template <template <typename> class S, EdgeType E>
requires SearcherType<S<E>>
class PathFinder final {
	const IGraph<E>& graph;
	std::vector<E>* edgeTo;
	uint32_t v;

public:
	class Path final : IPrintable {
		std::forward_list<E> edges;

	public:
		explicit Path(std::forward_list<E>&& edges){
			this->edges = std::move(edges);
		}

		Path(E additionalEdge, const Path& other)
			: edges(other.edges) {
			this->edges.push_front(additionalEdge);
		}

		const E* Front() const{ return &edges.front(); }
		bool HasFinished(uint32_t source) const{ return Front()->Other() == source; }
		std::forward_list<E> Edges() const{ return edges; }
		std::vector<uint32_t> Vertices() const{
			std::vector<uint32_t> vertices;
			for(const E& edge : Edges())
				vertices.push_back(edge.Other());
			return vertices;
		}

		std::ostream& Print(std::ostream& os) const override{
			size_t count = 0;
			for(auto v : Vertices()){
				if (count++ > 0) std::cout << " -> ";
				std::cout << v;
			}
			return os;
		}
	};

private:
	void Run(){
		S<E> search(graph);
		for(search.Start(v); !search.IsDone(); search.Next()){
			auto i = search.Current();
			for(auto& edge : i.Edges())
				edgeTo[i.Current()].push_back(edge);
		}
	}

	std::vector<Path> GetIncidentPathsOf(const Path& path) const{
		if(path.HasFinished(v))
			return { path };

		std::vector<Path> result;
		auto front = path.Front();
		for(auto edge : edgeTo[front->Either()]){
			Path newPath(edge, path);
			std::vector<Path> foundedPaths = GetIncidentPathsOf(newPath);
			std::copy(foundedPaths.begin(), foundedPaths.end(), std::back_inserter(result));
		}

		return result;
	}

public:
	explicit PathFinder(const IGraph<E>& graph, uint32_t vertex)
		: graph(graph), v(vertex){
		graph.CheckVertex(vertex);
		edgeTo = new std::vector<E>[graph.V()];
		Run();
	}

	~PathFinder(){ delete[] edgeTo; }
	PathFinder(PathFinder& other) = delete;
	PathFinder& operator=(const PathFinder& other) = delete;

	bool HasPathTo(uint32_t v){
		graph.CheckVertex(v);
		return edgeTo[v].size() > 0;
	}

	std::optional<Path> PathTo(uint32_t v){
		graph.CheckVertex(v);
		Path path({});
		return { };
	}

	std::vector<Path> PathsTo(uint32_t v) const{
		graph.CheckVertex(v);

		std::vector<Path> paths;
		for(auto edge : edgeTo[v]){
			Path path({ edge });
			auto incidentPaths = GetIncidentPathsOf(path);
			std::copy(incidentPaths.begin(), incidentPaths.end(), std::back_inserter(paths));
		}

		return paths;
	}

	uint32_t Source() const{ return v; }
};