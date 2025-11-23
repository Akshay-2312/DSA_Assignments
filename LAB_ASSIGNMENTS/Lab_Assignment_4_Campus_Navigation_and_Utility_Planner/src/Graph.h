#ifndef GRAPH_H
#define GRAPH_H

#include "BuildingADT.h"
#include <vector>
#include <map>
#include <limits>
#include <iostream>
using namespace std;

// Graph class for campus navigation
class Graph {
private:
    // Adjacency matrix representation
     vector< vector<int>> adjacencyMatrix;
    
    // Adjacency list representation
     map<int,  vector< pair<int, int>>> adjacencyList; // map<buildingID, vector<pair<buildingID, distance>>>
    
    // Map to store building IDs and their indices in the adjacency matrix
     map<int, int> buildingToIndex;
     vector<int> indexToBuilding;
    
    int numVertices;

public:
    Graph() : numVertices(0) {}
    
    // Add a new building to the graph
    void addBuilding(int buildingID) {
        // Check if building already exists
        if (buildingToIndex.find(buildingID) != buildingToIndex.end()) {
            return;
        }
        
        // Add to adjacency list
        adjacencyList[buildingID] =  vector< pair<int, int>>();
        
        // Add to adjacency matrix
        buildingToIndex[buildingID] = numVertices;
        indexToBuilding.push_back(buildingID);
        
        // Resize adjacency matrix
        adjacencyMatrix.resize(numVertices + 1,  vector<int>(numVertices + 1, 0));
        for (int i = 0; i < numVertices; i++) {
            adjacencyMatrix[i].resize(numVertices + 1, 0);
        }
        
        numVertices++;
    }
    
    // Add an edge between two buildings
    void addEdge(int buildingID1, int buildingID2, int distance) {
        // Check if buildings exist
        if (buildingToIndex.find(buildingID1) == buildingToIndex.end() || 
            buildingToIndex.find(buildingID2) == buildingToIndex.end()) {
             cout << "Building ID not found!" <<  endl;
            return;
        }
        
        // Add to adjacency list
        adjacencyList[buildingID1].push_back( make_pair(buildingID2, distance));
        adjacencyList[buildingID2].push_back( make_pair(buildingID1, distance)); // Undirected graph
        
        // Add to adjacency matrix
        int index1 = buildingToIndex[buildingID1];
        int index2 = buildingToIndex[buildingID2];
        adjacencyMatrix[index1][index2] = distance;
        adjacencyMatrix[index2][index1] = distance; // Undirected graph
    }
    
    // Get adjacency matrix
     vector< vector<int>> getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }
    
    // Get adjacency list
     map<int,  vector< pair<int, int>>> getAdjacencyList() const {
        return adjacencyList;
    }
    
    // Get number of vertices
    int getNumVertices() const {
        return numVertices;
    }
    
    // Get building ID from index
    int getBuildingID(int index) const {
        if (index >= 0 && index < numVertices) {
            return indexToBuilding[index];
        }
        return -1;
    }
    
    // Get index from building ID
    int getIndex(int buildingID) const {
        auto it = buildingToIndex.find(buildingID);
        if (it != buildingToIndex.end()) {
            return it->second;
        }
        return -1;
    }
    
    // Display adjacency matrix
    void displayAdjacencyMatrix() const {
         cout << "Adjacency Matrix:" <<  endl;
         cout << "    ";
        for (int i = 0; i < numVertices; i++) {
             cout << indexToBuilding[i] << " ";
        }
         cout <<  endl;
        
        for (int i = 0; i < numVertices; i++) {
             cout << indexToBuilding[i] << " | ";
            for (int j = 0; j < numVertices; j++) {
                 cout << adjacencyMatrix[i][j] << " ";
            }
             cout <<  endl;
        }
    }
    
    // Display adjacency list
    void displayAdjacencyList() const {
         cout << "Adjacency List:" <<  endl;
        for (const auto& pair : adjacencyList) {
             cout << "Building " << pair.first << " -> ";
            for (const auto& edge : pair.second) {
                 cout << "(" << edge.first << ", " << edge.second << ") ";
            }
             cout <<  endl;
        }
    }
};

#endif // GRAPH_H