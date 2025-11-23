#include "InventorySystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Constructor - Initialize arrays and variables
InventorySystem::InventorySystem(int r, int c) : itemCount(0), rows(r), cols(c) {
    // Initialize 1D array for items
    itemArray = new InventoryItem[MAX_ITEMS];
    
    // Initialize 2D array for price/quantity table
    priceQuantityTable = new float*[rows];
    for (int i = 0; i < rows; i++) {
        priceQuantityTable[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            priceQuantityTable[i][j] = 0.0f;
        }
    }
}

// Destructor - Free allocated memory
InventorySystem::~InventorySystem() {
    // Free 1D array
    delete[] itemArray;
    
    // Free 2D array
    for (int i = 0; i < rows; i++) {
        delete[] priceQuantityTable[i];
    }
    delete[] priceQuantityTable;
}

// Add a new item to the inventory - O(1) amortized
bool InventorySystem::addItemRecord(const InventoryItem& item) {
    // Check if array is full
    if (itemCount >= MAX_ITEMS) {
         cout << "Inventory is full. Cannot add more items.\n";
        return false;
    }
    
    // Check if item with same ID already exists
    for (int i = 0; i < itemCount; i++) {
        if (itemArray[i].getItemID() == item.getItemID()) {
             cout << "Item with ID " << item.getItemID() << " already exists.\n";
            return false;
        }
    }
    
    // Add item to array
    itemArray[itemCount] = item;
    itemCount++;
    
    // Update price/quantity table
    int id = item.getItemID() % rows; // Use modulo for row index
    int qty = item.getQuantity() % cols; // Use modulo for column index
    priceQuantityTable[id][qty] = item.getPrice();
    
     cout << "Item added successfully.\n";
    return true;
}

// Remove an item from inventory by ID - O(n)
bool InventorySystem::removeItemRecord(int itemID) {
    // Find item index
    int index = -1;
    for (int i = 0; i < itemCount; i++) {
        if (itemArray[i].getItemID() == itemID) {
            index = i;
            break;
        }
    }
    
    // If item not found
    if (index == -1) {
         cout << "Item with ID " << itemID << " not found.\n";
        return false;
    }
    
    // Remove from sparse items if present
    sparseItems.erase(itemID);
    
    // Shift items to fill the gap
    for (int i = index; i < itemCount - 1; i++) {
        itemArray[i] = itemArray[i + 1];
    }
    
    itemCount--;
     cout << "Item removed successfully.\n";
    return true;
}

// Search for an item by ID - O(n)
InventoryItem* InventorySystem::searchByItem(int itemID) {
    // Check sparse items first (faster if item is there)
    auto it = sparseItems.find(itemID);
    if (it != sparseItems.end()) {
         cout << "Item found in sparse storage.\n";
        return &(it->second);
    }
    
    // Search in main array
    for (int i = 0; i < itemCount; i++) {
        if (itemArray[i].getItemID() == itemID) {
            return &itemArray[i];
        }
    }
    
     cout << "Item with ID " << itemID << " not found.\n";
    return nullptr;
}

// Search for an item by name - O(n)
InventoryItem* InventorySystem::searchByItem(const  string& itemName) {
    // Search in main array
    for (int i = 0; i < itemCount; i++) {
        if (itemArray[i].getItemName() == itemName) {
            return &itemArray[i];
        }
    }
    
    // Search in sparse items
    for (auto& pair : sparseItems) {
        if (pair.second.getItemName() == itemName) {
             cout << "Item found in sparse storage.\n";
            return &(pair.second);
        }
    }
    
     cout << "Item with name '" << itemName << "' not found.\n";
    return nullptr;
}

// Manage price/quantity table - O(n×m)
void InventorySystem::managePriceQuantity(bool useRowMajor) {
     cout << "Updating price/quantity table...\n";
    
    // Update table based on current inventory
    for (int i = 0; i < itemCount; i++) {
        int id = itemArray[i].getItemID() % rows;
        int qty = itemArray[i].getQuantity() % cols;
        priceQuantityTable[id][qty] = itemArray[i].getPrice();
    }
    
    displayPriceQuantityTable(useRowMajor);
}

// Display price/quantity table - O(n×m)
void InventorySystem::displayPriceQuantityTable(bool useRowMajor) {
     cout << "\n===== Price/Quantity Table =====\n";
     cout << "Using " << (useRowMajor ? "Row-Major" : "Column-Major") << " Order\n\n";
    
    // Display column headers
     cout <<  setw(8) << "ID/Qty";
    for (int j = 0; j < cols; j++) {
         cout <<  setw(8) << j;
    }
     cout << "\n";
    
    // Display table content
    if (useRowMajor) {
        // Row-major traversal
        for (int i = 0; i < rows; i++) {
             cout <<  setw(8) << i;
            for (int j = 0; j < cols; j++) {
                 cout <<  setw(8) <<  fixed <<  setprecision(2) << priceQuantityTable[i][j];
            }
             cout << "\n";
        }
    } else {
        // Column-major traversal
        for (int i = 0; i < rows; i++) {
             cout <<  setw(8) << i;
            for (int j = 0; j < cols; j++) {
                 cout <<  setw(8) <<  fixed <<  setprecision(2) << priceQuantityTable[j][i];
            }
             cout << "\n";
        }
    }
     cout << "\n";
}

// Optimize storage for low-quantity items - O(n)
void InventorySystem::optimizeSparseStorage(int threshold) {
     cout << "Optimizing storage for items with quantity < " << threshold << "...\n";
    
    // Clear existing sparse items
    sparseItems.clear();
    
    // Find low-quantity items and move to sparse storage
    int sparseCount = 0;
    for (int i = 0; i < itemCount; i++) {
        if (itemArray[i].getQuantity() < threshold) {
            // Add to sparse storage
            sparseItems[itemArray[i].getItemID()] = itemArray[i];
            sparseCount++;
        }
    }
    
     cout << "Optimization complete. " << sparseCount << " items moved to sparse storage.\n";
    
    // Display sparse items
    displaySparseItems();
}

// Display sparse items - O(k)
void InventorySystem::displaySparseItems() {
     cout << "\n===== Sparse Storage Items (Low Quantity) =====\n";
    
    if (sparseItems.empty()) {
         cout << "No items in sparse storage.\n";
        return;
    }
    
     cout <<  left <<  setw(8) << "ID" 
              <<  setw(20) << "Name" 
              <<  setw(10) << "Quantity" 
              <<  setw(10) << "Price" << "\n";
     cout <<  string(48, '-') << "\n";
    
    for (const auto& pair : sparseItems) {
        const InventoryItem& item = pair.second;
         cout <<  left <<  setw(8) << item.getItemID() 
                  <<  setw(20) << item.getItemName() 
                  <<  setw(10) << item.getQuantity() 
                  <<  setw(10) <<  fixed <<  setprecision(2) << item.getPrice() << "\n";
    }
     cout << "\n";
}

// Display all items in inventory - O(n)
void InventorySystem::displayAllItems() {
     cout << "\n===== Inventory Items =====\n";
    
    if (itemCount == 0) {
         cout << "Inventory is empty.\n";
        return;
    }
    
     cout <<  left <<  setw(8) << "ID" 
              <<  setw(20) << "Name" 
              <<  setw(10) << "Quantity" 
              <<  setw(10) << "Price" 
              <<  setw(10) << "Total" << "\n";
     cout <<  string(58, '-') << "\n";
    
    for (int i = 0; i < itemCount; i++) {
         cout <<  left <<  setw(8) << itemArray[i].getItemID() 
                  <<  setw(20) << itemArray[i].getItemName() 
                  <<  setw(10) << itemArray[i].getQuantity() 
                  <<  setw(10) <<  fixed <<  setprecision(2) << itemArray[i].getPrice() 
                  <<  setw(10) <<  fixed <<  setprecision(2) << itemArray[i].getTotalValue() << "\n";
    }
     cout << "\n";
}

// Display complexity analysis - O(1)
void InventorySystem::displayComplexityAnalysis() {
     cout << "\n===== Complexity Analysis =====\n";
     cout <<  left <<  setw(25) << "Operation" 
              <<  setw(20) << "Time Complexity" 
              <<  setw(20) << "Space Complexity" << "\n";
     cout <<  string(65, '-') << "\n";
    
     cout <<  left <<  setw(25) << "insertItem()" 
              <<  setw(20) << "O(1) amortized" 
              <<  setw(20) << "O(1)" << "\n";
              
     cout <<  left <<  setw(25) << "deleteItem()" 
              <<  setw(20) << "O(n)" 
              <<  setw(20) << "O(1)" << "\n";
              
     cout <<  left <<  setw(25) << "searchItem()" 
              <<  setw(20) << "O(n)" 
              <<  setw(20) << "O(1)" << "\n";
              
     cout <<  left <<  setw(25) << "managePriceQuantity()" 
              <<  setw(20) << "O(n×m)" 
              <<  setw(20) << "O(1)" << "\n";
              
     cout <<  left <<  setw(25) << "optimizeSparseStorage()" 
              <<  setw(20) << "O(n)" 
              <<  setw(20) << "O(k)" << "\n";
    
     cout << "\nWhere:\n";
     cout << "  n = number of items in inventory\n";
     cout << "  m = size of price/quantity table\n";
     cout << "  k = number of sparse items (low quantity)\n\n";
}