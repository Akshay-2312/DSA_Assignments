#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <unordered_map>
#include <set>
#include "Graph.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "Tree.h"
#include "TopologicalSort.h"
#include "MST.h"
#include "Utils.h"

using namespace std;

void showMenu() {
    cout << "\n=== Smart City Road Navigation System ===\n";
    cout << "1) Add Zone (Node)\n";
    cout << "2) Add Road (Edge)\n";
    cout << "3) Show Graph (List + Matrix)\n";
    cout << "4) Shortest Path (Dijkstra)\n";
    cout << "5) All-Pairs Shortest Paths (Floyd–Warshall)\n";
    cout << "6) Index City Zones (Binary / AVL)\n";
    cout << "7) Construction Sequence (Topological Sort on directed graph)\n";
    cout << "8) Plan Road Network (Prim MST)\n";
    cout << "9) Exit\n";
    cout << "Choose: " << std::flush;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    Graph roadGraph(false); // undirected for roads/MST
    Graph constructionGraph(true); // directed for topological sort

    while (true) {
        showMenu();
        int choice; if (!(cin >> choice)) { Utils::clearInput(); continue; }
        if (choice == 9) break;

        if (choice == 1) {
            int id; string name, details;
            cout << "Enter Zone ID: "; cin >> id; Utils::clearInput();
            cout << "Enter Zone Name: "; getline(cin, name);
            cout << "Enter Zone Details: "; getline(cin, details);
            roadGraph.addNode(id, name, details);
            constructionGraph.addNode(id, name, details);
            cout << "Zone added: " << id << " - " << name << "\n";
        } else if (choice == 2) {
            int u,v; double w; cout << "From ID: "; cin >> u; cout << "To ID: "; cin >> v; cout << "Distance/Weight: "; cin >> w;
            roadGraph.addEdge(u,v,w); // undirected
            constructionGraph.addEdge(u,v,w); // directed edge for construction order
            cout << "Road added between " << u << " and " << v << " weight=" << w << "\n";
        } else if (choice == 3) {
            cout << "\n-- Adjacency List (Road Graph) --\n"; roadGraph.displayAdjList(cout);
            cout << "\n-- Adjacency Matrix (Road Graph) --\n"; roadGraph.displayAdjMatrix(cout);
        } else if (choice == 4) {
            int s,t; cout << "Source ID: "; cin >> s; cout << "Target ID: "; cin >> t;
            auto res = DijkstraSolver::shortestPath(roadGraph, s, t);
            if (!isfinite(res.distance)) cout << "No path found.\n";
            else {
                cout << "Shortest distance: " << res.distance << "\nPath: ";
                for (size_t i = 0; i < res.pathIds.size(); ++i) {
                    cout << res.pathIds[i]; if (i+1<res.pathIds.size()) cout << " -> ";
                }
                cout << "\n";
            }
        } else if (choice == 5) {
            auto fw = FloydWarshallSolver::solve(roadGraph);
            const auto &dist = fw.dist; int n = (int)dist.size();
            cout << "\nAll-Pairs Shortest Distances (by ID order):\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][j] >= 1e18/2) cout << "INF\t"; else cout << dist[i][j] << "\t";
                }
                cout << "\n";
            }
        } else if (choice == 6) {
            cout << "Insert into (1) Binary Tree or (2) AVL Tree? "; int t; cin >> t;
            if (t == 1) {
                ZoneBST bst;
                for (int idx = 0; idx < roadGraph.vertexCount(); ++idx) {
                    auto z = roadGraph.getZoneByIndex(idx);
                    bst.insert(z.id, z.name, z.details);
                }
                auto in = bst.inorder(); cout << "Inorder: "; for (auto &s: in) cout << s << " "; cout << "\n";
                auto pre = bst.preorder(); cout << "Preorder: "; for (auto &s: pre) cout << s << " "; cout << "\n";
                auto post = bst.postorder(); cout << "Postorder: "; for (auto &s: post) cout << s << " "; cout << "\n";
            } else {
                ZoneAVL avl;
                for (int idx = 0; idx < roadGraph.vertexCount(); ++idx) {
                    auto z = roadGraph.getZoneByIndex(idx);
                    avl.insert(z.id, z.name, z.details);
                }
                auto in = avl.inorder(); cout << "Inorder (AVL): "; for (auto &s: in) cout << s << " "; cout << "\n";
                auto pre = avl.preorder(); cout << "Preorder (AVL): "; for (auto &s: pre) cout << s << " "; cout << "\n";
                auto post = avl.postorder(); cout << "Postorder (AVL): "; for (auto &s: post) cout << s << " "; cout << "\n";
            }
        } else if (choice == 7) {
            auto order = TopologicalSorter::sortIds(constructionGraph);
            if (order.empty()) cout << "Graph has cycles; cannot perform topological sort.\n";
            else { cout << "Construction order: "; for (size_t i=0;i<order.size();++i){ cout<<order[i]; if(i+1<order.size()) cout<<" -> "; } cout<<"\n"; }
        } else if (choice == 8) {
            auto mst = PrimMST::build(roadGraph);
            cout << "MST total weight: " << mst.totalWeight << "\nEdges:\n";
            for (auto &e : mst.edges) cout << e.fromId << " - " << e.toId << " (" << e.weight << ")\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }
    cout << "Goodbye!\n";
    return 0;
}