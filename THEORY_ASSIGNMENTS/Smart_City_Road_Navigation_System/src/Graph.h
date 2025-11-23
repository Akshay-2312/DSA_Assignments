#pragma once
#include <bits/stdc++.h>

class Graph {
public:
    struct Zone {
        int id;
        std::string name;
        std::string details;
    };

private:
    bool directed;

    // Node bookkeeping
    std::unordered_map<int, int> id_to_index;
    std::vector<int> index_to_id;
    std::vector<Zone> zones;

    // Representations
    std::vector<std::vector<std::pair<int, double>>> adjList; // index-based
    std::vector<std::vector<double>> adjMatrix;                // index-based

    static constexpr double INF = 1e18;

    void ensureMatrixSize() {
        int n = (int)index_to_id.size();
        adjMatrix.assign(n, std::vector<double>(n, INF));
        for (int i = 0; i < n; ++i) adjMatrix[i][i] = 0.0;
    }

public:
    Graph(bool directed_ = false) : directed(directed_) {}

    bool isDirected() const { return directed; }

    bool hasNode(int id) const { return id_to_index.find(id) != id_to_index.end(); }

    int addNode(int id, const std::string &name, const std::string &details) {
        if (hasNode(id)) return id_to_index[id];
        int idx = (int)index_to_id.size();
        id_to_index[id] = idx;
        index_to_id.push_back(id);
        zones.push_back({id, name, details});
        adjList.emplace_back();
        ensureMatrixSize();
        return idx;
    }

    void addEdge(int fromId, int toId, double weight) {
        if (!hasNode(fromId) || !hasNode(toId)) return;
        int u = id_to_index[fromId];
        int v = id_to_index[toId];
        // Adjacency list
        adjList[u].push_back({v, weight});
        if (!directed) adjList[v].push_back({u, weight});
        // Adjacency matrix
        adjMatrix[u][v] = std::min(adjMatrix[u][v], weight);
        if (!directed) adjMatrix[v][u] = std::min(adjMatrix[v][u], weight);
    }

    int vertexCount() const { return (int)index_to_id.size(); }

    const std::vector<std::vector<std::pair<int, double>>> &getAdjList() const { return adjList; }
    const std::vector<std::vector<double>> &getAdjMatrix() const { return adjMatrix; }

    const std::vector<int> &getIndexToId() const { return index_to_id; }
    int getIndex(int id) const { auto it = id_to_index.find(id); return it == id_to_index.end() ? -1 : it->second; }
    int getIdByIndex(int index) const { return index_to_id.at(index); }

    const Zone &getZoneById(int id) const { return zones.at(id_to_index.at(id)); }
    const Zone &getZoneByIndex(int index) const { return zones.at(index); }

    void displayAdjList(std::ostream &os) const {
        os << "Adjacency List (index: id -> (neighbor_id, weight))\n";
        for (int u = 0; u < (int)adjList.size(); ++u) {
            os << "[" << u << "] " << getIdByIndex(u) << " -> ";
            for (auto &p : adjList[u]) {
                int v = p.first; double w = p.second;
                os << "(" << getIdByIndex(v) << ", " << w << ") ";
            }
            os << "\n";
        }
    }

    void displayAdjMatrix(std::ostream &os) const {
        os << "Adjacency Matrix (id order)\n";
        int n = vertexCount();
        os << "   ";
        for (int j = 0; j < n; ++j) os << getIdByIndex(j) << "\t";
        os << "\n";
        for (int i = 0; i < n; ++i) {
            os << getIdByIndex(i) << "\t";
            for (int j = 0; j < n; ++j) {
                double val = adjMatrix[i][j];
                if (val >= INF/2) os << "INF\t";
                else os << val << "\t";
            }
            os << "\n";
        }
    }
};