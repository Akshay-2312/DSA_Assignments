#pragma once
#include <bits/stdc++.h>
#include "Graph.h"

struct DijkstraResult {
    double distance;
    std::vector<int> pathIds; // sequence of node IDs
};

class DijkstraSolver {
public:
    static DijkstraResult shortestPath(const Graph &g, int startId, int endId) {
        int n = g.vertexCount();
        int s = g.getIndex(startId);
        int t = g.getIndex(endId);
        DijkstraResult res{.distance = std::numeric_limits<double>::infinity(), .pathIds = {}};
        if (s < 0 || t < 0 || n == 0) return res;

        const auto &adj = g.getAdjList();
        std::vector<double> dist(n, std::numeric_limits<double>::infinity());
        std::vector<int> parent(n, -1);
        using P = std::pair<double,int>; // (dist, node)
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

        dist[s] = 0.0;
        pq.push({0.0, s});
        while (!pq.empty()) {
            auto [d,u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            if (u == t) break;
            for (auto &edge : adj[u]) {
                int v = edge.first; double w = edge.second;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (!std::isfinite(dist[t])) return res;
        res.distance = dist[t];
        // reconstruct path (indices -> ids)
        std::vector<int> pathIdx;
        for (int cur = t; cur != -1; cur = parent[cur]) pathIdx.push_back(cur);
        std::reverse(pathIdx.begin(), pathIdx.end());
        for (int idx : pathIdx) res.pathIds.push_back(g.getIdByIndex(idx));
        return res;
    }
};