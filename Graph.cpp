#include "Graph.h"
#include <fstream>
#include <queue>
#include <unordered_set>

void Graph::InsertNode(const Node &node)
{
    nodes.push_back(node);
}

void Graph::InsertEdge(const Edge &edge)
{
    edges.push_back(edge);
}

const Node &Graph::GetNode(const size_t &index) const noexcept
{
    return nodes[index];
}

const std::vector<Node> &Graph::GetNodes() const noexcept
{
    return nodes;
}

const std::vector<Edge> &Graph::GetEdges() const noexcept
{
    return edges;
}

size_t Graph::GetNumberOfNodes() const noexcept
{
    return nodes.size();
}

size_t Graph::GetNumberOfEdges() const noexcept
{
    return nodes.size();
}

void Graph::GenerateAdjacencyLists()
{
    adjacencyLists.resize(GetNumberOfNodes());

    for(const auto& edge : edges)
    {
        adjacencyLists[edge.GetFirstNode()].push_back(std::make_pair(edge.GetLastNode(), edge.GetLength()));
    }

    // PrintAdjacencyLists("adjacencyLists.txt");
}

void Graph::PrintAdjacencyLists(const std::string &filename)
{
    std::ofstream fout(filename);

    for(size_t index = 0; index < adjacencyLists.size(); ++index)
    {
        fout << "L[" << index << "]: ";
        for(const auto& neighbour : adjacencyLists[index])
            fout << "(" << neighbour.first << " " << neighbour.second << ") ";
        fout << std::endl;
    }
}

std::vector<size_t> Graph::GetPath(const size_t &start, const size_t &end, const std::vector<int> &cameFrom)
{
    std::vector<size_t> path;
    path.push_back(end);

    int node = cameFrom[end];

    while (node != (int)start)
    {
        path.push_back(node);
        node = cameFrom[node];
    }

    path.push_back(start);
    return path;
}

std::vector<size_t> Graph::DijkstraAlgorithm(const size_t &start, const size_t &end)
{
    std::vector<size_t> distances(GetNumberOfNodes(), SIZE_MAX);
    std::vector<int> cameFrom(GetNumberOfNodes(), -1);

    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    distances[start] = 0;
    pq.push(std::make_pair(distances[start], start));

    while (!pq.empty())
    {
        size_t currNode = pq.top().second;
        pq.pop();

        if (currNode == end)
            break;

        for(const auto& [neighbour, cost] : adjacencyLists[currNode])
            if (distances[neighbour] > distances[currNode] + cost)
            {
                distances[neighbour] = distances[currNode] + cost;
                cameFrom[neighbour] = currNode;
                pq.push(std::make_pair(distances[neighbour], neighbour));
            }
    }

    return GetPath(start, end, cameFrom);
}
