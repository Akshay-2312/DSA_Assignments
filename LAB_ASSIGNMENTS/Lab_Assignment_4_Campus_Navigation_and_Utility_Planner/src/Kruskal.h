#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Graph.h"
#include <algorithm>
#include <vector>
using namespace std;

// Edge structure for Kruskal's algorithm
struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set data structure for Kruskal's algorithm
class DisjointSet {
private:
     vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        // Initialize each element as a separate set
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find the set of an element (with path compression)
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union of two sets (by rank)
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Attach smaller rank tree under root of higher rank tree
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            // If ranks are same, make one as root and increment its rank
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Kruskal's algorithm for minimum spanning tree
class Kruskal {
private:
    const Graph& graph;
    
public:
    Kruskal(const Graph& g) : graph(g) {}
    
    // Find minimum spanning tree
     vector<Edge> findMinimumSpanningTree() {
         vector<Edge> result;
         vector<Edge> edges;
        
        // Get adjacency list
        auto adjacencyList = graph.getAdjacencyList();
        
        // Create edges from adjacency list
        for (const auto& pair : adjacencyList) {
            int src = pair.first;
            for (const auto& edge : pair.second) {
                int dest = edge.first;
                int weight = edge.second;
                
                // Add edge only once (since graph is undirected)
                if (src < dest) {
                    edges.push_back(Edge(src, dest, weight));
                }
            }
        }
        
        // Sort edges by weight
         sort(edges.begin(), edges.end());
        
        // Create disjoint set
        DisjointSet ds(graph.getNumVertices() + 1);
        
        // Process edges
        for (const auto& edge : edges) {
            int srcIndex = graph.getIndex(edge.src);
            int destIndex = graph.getIndex(edge.dest);
            
            // Check if adding this edge creates a cycle
            if (ds.find(srcIndex) != ds.find(destIndex)) {
                // Add edge to result
                result.push_back(edge);
                
                // Union sets
                ds.unionSets(srcIndex, destIndex);
            }
        }
        
        return result;
    }
    
    // Display minimum spanning tree
    void displayMinimumSpanningTree() {
         vector<Edge> mst = findMinimumSpanningTree();
        
        if (mst.empty()) {
             cout << "No minimum spanning tree exists." <<  endl;
            return;
        }
        
        int totalWeight = 0;
        
         cout << "Minimum Spanning Tree (Utility Cable Layout):" <<  endl;
         cout << "Edge \tWeight" <<  endl;
        
        for (const auto& edge : mst) {
             cout << edge.src << " - " << edge.dest << "\t" << edge.weight <<  endl;
            totalWeight += edge.weight;
        }
        
         cout << "Total Cable Length: " << totalWeight <<  endl;
    }
};

#endif // KRUSKAL_H