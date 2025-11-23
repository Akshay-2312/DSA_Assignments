#pragma once
#include <bits/stdc++.h>
#include "Graph.h"

struct FloydWarshallResult {
    std::vector<std::vector<double>> dist; // distances by index
};

class FloydWarshallSolver {
public:
    static FloydWarshallResult solve(const Graph &g) {
        const auto &mat = g.getAdjMatrix();
        int n = (int)mat.size();
        const double INF = 1e18;
        FloydWarshallResult res;
        res.dist = mat; // copy
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (res.dist[i][k] < INF/2 && res.dist[k][j] < INF/2) {
                        res.dist[i][j] = std::min(res.dist[i][j], res.dist[i][k] + res.dist[k][j]);
                    }
                }
            }
        }
        return res;
    }
};