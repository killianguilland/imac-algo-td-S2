#include "graph.hpp"

namespace Graph {
    bool WeightedGraphEdge::operator==(WeightedGraphEdge const& other) const {
        return to == other.to && weight == other.weight;
    }
    bool WeightedGraphEdge:: operator!=(WeightedGraphEdge const& other) const {
        return !(*this == other);
    }

    bool WeightedGraph::operator==(WeightedGraph const& other) const {
        return adjacency_list == other.adjacency_list;
    }

    bool WeightedGraph::operator!=(WeightedGraph const& other) const {
        return !(*this == other);
    }

    void WeightedGraph::add_vertex(int const id) {
        if (adjacency_list.find(id) == adjacency_list.end()) {
            adjacency_list[id] = std::vector<WeightedGraphEdge>();
        }
    }

    void WeightedGraph::add_directed_edge(int const from, int const to, float const weight) {
        add_vertex(from);
        add_vertex(to);
        adjacency_list[from].push_back(WeightedGraphEdge{to, weight});
    }

    void WeightedGraph::add_undirected_edge(int const from, int const to, float const weight) {
        add_directed_edge(from, to, weight);
        add_directed_edge(to, from, weight);
    }

    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
        WeightedGraph graph;
        size_t size = adjacency_matrix.size();
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                float weight = adjacency_matrix[i][j];
                if (weight != 0.0f) {
                    graph.add_directed_edge(i, j, weight);
                }
            }
        }
        return graph;
    }

    void WeightedGraph::print_DFS(int const start) const {
        std::vector<bool> visited(adjacency_list.size(), false);
        std::stack<int> s;
        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int vertex = s.top();
            s.pop();
            std::cout << vertex << " ";
            for (const auto& edge : adjacency_list.at(vertex)) {
                if (edge.to >= 0 && edge.to < static_cast<int>(visited.size()) && !visited[edge.to]) {
                    visited[edge.to] = true;
                    s.push(edge.to);
                }
            }
        }
        std::cout << std::endl;
    }

    void WeightedGraph::print_BFS(int const start, std::function<void(int const)> const& callback) const {
        std::vector<bool> visited(adjacency_list.size(), false);
        std::queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            callback(vertex);
            for (const auto& edge : adjacency_list.at(vertex)) {
                if (edge.to >= 0 && edge.to < static_cast<int>(visited.size()) && !visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
    }

    void WeightedGraph::print_BFS(int const start) const {
        print_BFS(start, [](int const vertex) {
            std::cout << vertex << " ";
        });
    }
}