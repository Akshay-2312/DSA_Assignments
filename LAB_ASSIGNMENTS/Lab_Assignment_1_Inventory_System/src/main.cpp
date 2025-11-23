#include "InventorySystem.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display menu
void displayMenu() {
    cout << "\n===== Grocery Inventory Management System =====\n";
    cout << "1. Add Item\n";
    cout << "2. Delete Item\n";
    cout << "3. Search Item\n";
    cout << "4. Show All Items\n";
    cout << "5. Manage Price/Quantity Table\n";
    cout << "6. Optimize Sparse Storage\n";
    cout << "7. Display Complexity Analysis\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // Create inventory system with 10x10 price/quantity table
    InventorySystem inventory(10, 10);
    int choice;
    bool running = true;
    
    cout << "Welcome to Grocery Inventory Management System\n";
    
    while (running) {
        displayMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1: { // Add Item
                int id, quantity;
                string name;
                float price;
                
                cout << "\n----- Add New Item -----\n";
                cout << "Enter Item ID: ";
                cin >> id;
                clearInputBuffer();
                
                cout << "Enter Item Name: ";
                getline(cin, name);
                
                cout << "Enter Quantity: ";
                cin >> quantity;
                clearInputBuffer();
                
                cout << "Enter Price: $";
                cin >> price;
                clearInputBuffer();
                
                InventoryItem newItem(id, name, quantity, price);
                inventory.addItemRecord(newItem);
                break;
            }
            
            case 2: { // Delete Item
                int id;
                cout << "\n----- Delete Item -----\n";
                cout << "Enter Item ID to delete: ";
                cin >> id;      
                clearInputBuffer();
                
                inventory.removeItemRecord(id);
                break;
            }
            
            case 3: { // Search Item
                int searchChoice;
                cout << "\n----- Search Item -----\n";
                cout << "1. Search by ID\n";
                cout << "2. Search by Name\n";
                cout << "Enter your choice: ";
                cin >> searchChoice;    
                clearInputBuffer();
                
                InventoryItem* foundItem = nullptr;
                
                if (searchChoice == 1) {
                    int id;
                    cout << "Enter Item ID: ";
                    cin >> id;
                    clearInputBuffer();
                    
                    foundItem = inventory.searchByItem(id);
                } else if (searchChoice == 2) {
                    string name;
                    cout << "Enter Item Name: ";
                    getline(cin, name);
                    
                    foundItem = inventory.searchByItem(name);
                } else {
                    cout << "Invalid choice.\n";
                    break;
                }
                
                if (foundItem) {
                    cout << "\n----- Item Found -----\n";
                    cout << "ID: " << foundItem->getItemID() << "\n";
                    cout << "Name: " << foundItem->getItemName() << "\n";
                    cout << "Quantity: " << foundItem->getQuantity() << "\n";
                    cout << "Price: $" << foundItem->getPrice() << "\n";
                    cout << "Total Value: $" << foundItem->getTotalValue() << "\n"; 
                }
                break;
            }
            
            case 4: { // Show All Items
                inventory.displayAllItems();
                break;
            }
            
            case 5: { // Manage Price/Quantity Table
                int tableChoice;
                 cout << "\n----- Price/Quantity Table -----\n";
                 cout << "1. Display using Row-Major Order\n";
                 cout << "2. Display using Column-Major Order\n";
                 cout << "Enter your choice: ";
                 cin >> tableChoice;
                clearInputBuffer();
                
                if (tableChoice == 1) {
                    inventory.managePriceQuantity(true); // Row-major
                } else if (tableChoice == 2) {
                    inventory.managePriceQuantity(false); // Column-major
                } else {
                     cout << "Invalid choice.\n";
                }
                break;
            }
            
            case 6: { // Optimize Sparse Storage
                int threshold;
                 cout << "\n----- Optimize Sparse Storage -----\n";
                 cout << "Enter quantity threshold (items below this will be moved to sparse storage): ";
                 cin >> threshold;
                clearInputBuffer();
                
                inventory.optimizeSparseStorage(threshold);
                break;
            }
            
            case 7: { // Display Complexity Analysis
                inventory.displayComplexityAnalysis();
                break;
            }
            
            case 8: { // Exit
                 cout << "Thank you for using Grocery Inventory Management System. Goodbye!\n";
                running = false;
                break;
            }
            
            default:
                 cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}