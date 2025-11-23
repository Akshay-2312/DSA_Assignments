#ifndef BUILDING_ADT_H
#define BUILDING_ADT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Building Data ADT
class Building {
private:
    int buildingID;
    string buildingName;
    string locationDetails;
    // Adjacency representation for connected buildings with distances
    vector<pair<int, int>> connections; // pair<buildingID, distance>

public:
    // Constructor
    Building(int id = 0, string name = "", string location = "") 
        : buildingID(id), buildingName(name), locationDetails(location) {}

    // Getters
    int getBuildingID() const { return buildingID; }
    string getBuildingName() const { return buildingName; }
    string getLocationDetails() const { return locationDetails; }
    vector<pair<int, int>> getConnections() const { return connections; }

    // Setters
    void setBuildingID(int id) { buildingID = id; }
    void setBuildingName(string name) { buildingName = name; }
    void setLocationDetails(string location) { locationDetails = location; }
    
    // Connection management
    void addConnection(int buildingID, int distance) {
        connections.push_back(make_pair(buildingID, distance));     
    }
    
    void removeConnection(int buildingID) {
        for (auto it = connections.begin(); it != connections.end(); ++it) {
            if (it->first == buildingID) {
                connections.erase(it);
                break;
            }
        }
    }
    
    // Display building information
    void displayInfo() const {
         cout << "Building ID: " << buildingID <<  endl;
         cout << "Building Name: " << buildingName <<  endl;
         cout << "Location Details: " << locationDetails <<  endl;
         cout << "Connections: " <<  endl;
        for (const auto& conn : connections) {
             cout << "  Connected to Building ID: " << conn.first 
                      << " with distance: " << conn.second <<  endl;
        }
    }
    
    // Comparison operators for BST/AVL operations
    bool operator<(const Building& other) const {
        return buildingID < other.buildingID;
    }
    
    bool operator>(const Building& other) const {
        return buildingID > other.buildingID;
    }
    
    bool operator==(const Building& other) const {
        return buildingID == other.buildingID;
    }
};

#endif // BUILDING_ADT_H