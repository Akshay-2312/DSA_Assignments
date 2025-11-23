#pragma once
#include <bits/stdc++.h>
#include "Graph.h"

struct MSTEdge { int fromId; int toId; double weight; };
struct MSTResult { double totalWeight; std::vector<MSTEdge> edges; };

class PrimMST {
public:
    static MSTResult build(const Graph &g) {
        MSTResult res{.totalWeight = 0.0, .edges = {}};
        int n = g.vertexCount();
        if (n == 0) return res;
        const auto &adj = g.getAdjList();
        std::vector<bool> inMST(n, false);
        using Edge = std::tuple<double,int,int>; // (w,u,v) index-based
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

        int start = 0;
        inMST[start] = true;
        for (auto &e : adj[start]) pq.emplace(e.second, start, e.first);

        int added = 1;
        while (added < n && !pq.empty()) {
            auto [w,u,v] = pq.top(); pq.pop();
            if (inMST[v]) continue;
            inMST[v] = true; ++added;
            res.totalWeight += w;
            res.edges.push_back({g.getIdByIndex(u), g.getIdByIndex(v), w});
            for (auto &e : adj[v]) if (!inMST[e.first]) pq.emplace(e.second, v, e.first);
        }
        return res;
    }
};