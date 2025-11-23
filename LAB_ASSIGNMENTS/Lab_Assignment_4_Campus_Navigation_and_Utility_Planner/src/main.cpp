#include <iostream>
#include <limits>
#include "BuildingADT.h"
#include "Tree.h"
#include "Graph.h"
#include "Dijkstra.h"
#include "Kruskal.h"
#include "ExpressionTree.h"
using namespace std;

// Function to clear input buffer
void clearInputBuffer() {
     cin.clear();
     cin.ignore( numeric_limits< streamsize>::max(), '\n');
}

// Function to display menu
void displayMenu() {
     cout << "\n========= CAMPUS NAVIGATION AND UTILITY PLANNER =========" <<  endl;
     cout << "1. Add New Building Record" <<  endl;
     cout << "2. List Campus Buildings (Inorder/Preorder/Postorder)" <<  endl;
     cout << "3. Construct Campus Graph" <<  endl;
     cout << "4. Find Optimal Navigation Path (Dijkstra)" <<  endl;
     cout << "5. Plan Utility Cable Layout (Kruskal)" <<  endl;
     cout << "6. Evaluate Energy Bill (Expression Tree)" <<  endl;
     cout << "7. Exit" <<  endl;
     cout << "==========================================================" <<  endl;
     cout << "Enter your choice: ";
}

int main() {
    // Initialize data structures
    BuildingAVL buildingTree;
    Graph campusGraph;
    bool graphConstructed = false;
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
         cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                // Add New Building Record
                int id;
                 string name, location;
                
                 cout << "\n--- Add New Building Record ---" <<  endl;
                 cout << "Enter Building ID: ";
                 cin >> id;
                clearInputBuffer();
                
                 cout << "Enter Building Name: ";
                 getline( cin, name);
                
                 cout << "Enter Location Details: ";
                 getline( cin, location);
                
                Building newBuilding(id, name, location);
                buildingTree.insert(newBuilding);
                
                 cout << "Building added successfully!" <<  endl;
                break;
            }
            case 2: {
                // List Campus Buildings
                int traversalChoice;
                 cout << "\n--- List Campus Buildings ---" <<  endl;
                 cout << "Select Traversal Type:" <<  endl;
                 cout << "1. Inorder Traversal" <<  endl;
                 cout << "2. Preorder Traversal" <<  endl;
                 cout << "3. Postorder Traversal" <<  endl;
                 cout << "Enter choice: ";
                 cin >> traversalChoice;
                clearInputBuffer();
                
                 vector<Building> buildings;
                
                switch (traversalChoice) {
                    case 1:
                        buildings = buildingTree.inorder();
                         cout << "\nInorder Traversal Result:" <<  endl;
                        break;
                    case 2:
                        buildings = buildingTree.preorder();
                         cout << "\nPreorder Traversal Result:" <<  endl;
                        break;
                    case 3:
                        buildings = buildingTree.postorder();
                         cout << "\nPostorder Traversal Result:" <<  endl;
                        break;
                    default:
                         cout << "Invalid choice. Using Inorder Traversal." <<  endl;
                        buildings = buildingTree.inorder();
                         cout << "\nInorder Traversal Result:" <<  endl;
                }
                
                if (buildings.empty()) {
                     cout << "No buildings found." <<  endl;
                } else {
                    for (const auto& building : buildings) {
                         cout << "Building ID: " << building.getBuildingID()
                                  << ", Name: " << building.getBuildingName()
                                  << ", Location: " << building.getLocationDetails() <<  endl;
                    }
                }
                break;
            }
            case 3: {
                // Construct Campus Graph
                 cout << "\n--- Construct Campus Graph ---" <<  endl;
                
                // Get all buildings
                 vector<Building> buildings = buildingTree.inorder();
                
                if (buildings.empty()) {
                     cout << "No buildings found. Please add buildings first." <<  endl;
                    break;
                }
                
                // Create a new graph
                campusGraph = Graph();
                
                // Add all buildings to the graph
                for (const auto& building : buildings) {
                    campusGraph.addBuilding(building.getBuildingID());
                }
                
                // Add connections between buildings
                char addMore = 'y';
                while (addMore == 'y' || addMore == 'Y') {
                    int buildingID1, buildingID2, distance;
                    
                     cout << "Enter first Building ID: ";
                     cin >> buildingID1;
                    clearInputBuffer();
                    
                     cout << "Enter second Building ID: ";
                     cin >> buildingID2;
                    clearInputBuffer();
                    
                     cout << "Enter distance between buildings: ";
                     cin >> distance;
                    clearInputBuffer();
                    
                    campusGraph.addEdge(buildingID1, buildingID2, distance);
                    
                     cout << "Add more connections? (y/n): ";
                     cin >> addMore;
                    clearInputBuffer();
                }
                
                // Display the graph
                 cout << "\nCampus Graph Constructed:" <<  endl;
                campusGraph.displayAdjacencyList();
                
                graphConstructed = true;
                 cout << "Campus graph constructed successfully!" <<  endl;
                break;
            }
            case 4: {
                // Find Optimal Navigation Path (Dijkstra)
                if (!graphConstructed) {
                     cout << "Please construct the campus graph first (Option 3)." <<  endl;
                    break;
                }
                
                 cout << "\n--- Find Optimal Navigation Path ---" <<  endl;
                int startID, endID;
                
                 cout << "Enter starting Building ID: ";
                 cin >> startID;
                clearInputBuffer();
                
                 cout << "Enter destination Building ID: ";
                 cin >> endID;
                clearInputBuffer();
                
                Dijkstra dijkstra(campusGraph);
                dijkstra.displayShortestPath(startID, endID);
                break;
            }
            case 5: {
                // Plan Utility Cable Layout (Kruskal)
                if (!graphConstructed) {
                     cout << "Please construct the campus graph first (Option 3)." <<  endl;
                    break;
                }
                
                 cout << "\n--- Plan Utility Cable Layout ---" <<  endl;
                Kruskal kruskal(campusGraph);
                kruskal.displayMinimumSpanningTree();
                break;
            }
            case 6: {
                // Evaluate Energy Bill (Expression Tree)
                 cout << "\n--- Evaluate Energy Bill ---" <<  endl;
                 string expression;
                
                 cout << "Enter arithmetic expression for energy bill calculation:" <<  endl;
                 cout << "(e.g., (100 * 0.15) + (50 * 0.2))" <<  endl;
                 getline( cin, expression);
                
                ExpressionTree expTree;
                double result = expTree.evaluateExpression(expression);
                
                 cout << "Expression: " << expression <<  endl;
                expTree.printExpression();
                 cout << "Evaluated Result: $" << result <<  endl;
                break;
            }
            case 7: {
                // Exit
                 cout << "Exiting Campus Navigation and Utility Planner. Goodbye!" <<  endl;
                running = false;
                break;
            }
            default: {
                 cout << "Invalid choice. Please try again." <<  endl;
                break;
            }
        }
    }
    
    return 0;
}