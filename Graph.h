#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"
#include <string>
#include <unordered_map>
#include <vector>

class Graph
{
public:
    using Pair = std::pair<size_t, size_t>;

public:
    Graph() = default;

    void InsertNode(const Node&);
    void InsertEdge(const Edge&);

    const Node &GetNode(const size_t&) const noexcept;

    const std::vector<Node> &GetNodes() const noexcept;
    const std::vector<Edge> &GetEdges() const noexcept;

    size_t GetNumberOfNodes() const noexcept;
    size_t GetNumberOfEdges() const noexcept;

    void GenerateAdjacencyLists();
    void PrintAdjacencyLists(const std::string&);

    std::vector<size_t> GetPath(const size_t&, const size_t&, const std::vector<int>&);
    std::vector<size_t> DijkstraAlgorithm(const size_t&, const size_t&);

private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::vector<std::vector<Pair>> adjacencyLists;
};

#endif // GRAPH_H
