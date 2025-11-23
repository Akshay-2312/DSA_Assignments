#pragma once
#include <bits/stdc++.h>
#include "Graph.h"

class TopologicalSorter {
public:
    static std::vector<int> sortIds(const Graph &g) {
        // Kahn's algorithm over adjacency list
        const auto &adj = g.getAdjList();
        int n = (int)adj.size();
        std::vector<int> indeg(n, 0);
        for (int u = 0; u < n; ++u) for (auto &e : adj[u]) indeg[e.first]++;

        std::queue<int> q;
        for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
        std::vector<int> orderIds;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            orderIds.push_back(g.getIdByIndex(u));
            for (auto &e : adj[u]) {
                int v = e.first; if (--indeg[v] == 0) q.push(v);
            }
        }
        if ((int)orderIds.size() != n) {
            // cycle detected; return empty to indicate failure
            return {};
        }
        return orderIds;
    }
};