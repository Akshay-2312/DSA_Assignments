#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <queue>
#include <limits>
#include <vector>
#include <map>
using namespace std;

// Dijkstra's algorithm for finding shortest path
class Dijkstra {
private:
    const Graph& graph;

public:
    Dijkstra(const Graph& g) : graph(g) {}

    // Find shortest path using adjacency list
     pair< vector<int>,  vector<int>> findShortestPath(int startBuildingID, int endBuildingID) {
        auto adjacencyList = graph.getAdjacencyList();
        
        // Check if buildings exist
        if (adjacencyList.find(startBuildingID) == adjacencyList.end() || 
            adjacencyList.find(endBuildingID) == adjacencyList.end()) {
            return {}; // Return empty path if buildings don't exist
        }
        
        // Initialize distances and previous nodes
         map<int, int> distance;
         map<int, int> previous;
        
        // Set all distances to infinity
        for (const auto& pair : adjacencyList) {
            distance[pair.first] =  numeric_limits<int>::max();
            previous[pair.first] = -1;
        }
        
        // Distance from start to itself is 0
        distance[startBuildingID] = 0;
        
        // Priority queue for Dijkstra's algorithm
        // pair<distance, buildingID>
         priority_queue< pair<int, int>,  vector< pair<int, int>>,  greater< pair<int, int>>> pq;
        pq.push( make_pair(0, startBuildingID));
        
        // Process vertices
        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentBuilding = pq.top().second;
            pq.pop();
            
            // If we've reached the destination, we can stop
            if (currentBuilding == endBuildingID) {
                break;
            }
            
            // If we've already found a better path, skip
            if (currentDistance > distance[currentBuilding]) {
                continue;
            }
            
            // Check all neighbors
            for (const auto& neighbor : adjacencyList[currentBuilding]) {
                int neighborBuilding = neighbor.first;
                int edgeWeight = neighbor.second;
                
                // Calculate new distance
                int newDistance = distance[currentBuilding] + edgeWeight;
                
                // If we found a better path, update
                if (newDistance < distance[neighborBuilding]) {
                    distance[neighborBuilding] = newDistance;
                    previous[neighborBuilding] = currentBuilding;
                    pq.push( make_pair(newDistance, neighborBuilding));
                }
            }
        }
        
        // Reconstruct path
         vector<int> path;
        for (int at = endBuildingID; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        
        // Reverse path to get start to end
         reverse(path.begin(), path.end());
        
        // If path doesn't start with startBuildingID, no path exists
        if (path.empty() || path[0] != startBuildingID) {
            return {};
        }
        
        // Create distances vector
         vector<int> distances;
        for (size_t i = 0; i < path.size(); i++) {
            if (i == 0) {
                distances.push_back(0);
            } else {
                distances.push_back(distance[path[i]]);
            }
        }
        
        return  make_pair(path, distances);
    }
    
    // Display the shortest path
    void displayShortestPath(int startBuildingID, int endBuildingID) {
        auto result = findShortestPath(startBuildingID, endBuildingID);
        auto path = result.first;
        auto distances = result.second;
        
        if (path.empty()) {
             cout << "No path exists between Building " << startBuildingID << " and Building " << endBuildingID <<  endl;
            return;
        }
        
         cout << "Shortest Path from Building " << startBuildingID << " to Building " << endBuildingID << ":" <<  endl;
         cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
             cout << path[i];
            if (i < path.size() - 1) {
                 cout << " -> ";
            }
        }
         cout <<  endl;
        
         cout << "Total Distance: " << distances.back() <<  endl;
    }
};

#endif // DIJKSTRA_H