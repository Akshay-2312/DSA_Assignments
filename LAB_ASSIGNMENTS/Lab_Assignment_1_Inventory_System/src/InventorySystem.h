#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include "InventoryItem.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

// Inventory Management System class
class InventorySystem {
private:
    static const int MAX_ITEMS = 100;
    InventoryItem* itemArray;                  // 1D array for items
    float** priceQuantityTable;                // 2D array for price/quantity
    map<int, InventoryItem> sparseItems;  // Sparse representation for low-stock items
    int itemCount;
    int rows, cols;                            // Dimensions for 2D array

public:
    // Constructor and destructor
    InventorySystem(int r = 10, int c = 10);
    ~InventorySystem();
    
    // Core operations
    bool addItemRecord(const InventoryItem& item);                // O(1) amortized
    bool removeItemRecord(int itemID);                            // O(n)
    InventoryItem* searchByItem(int itemID);                      // O(n)
    InventoryItem* searchByItem(const  string& itemName);     // O(n)
    
    // 2D array operations
    void managePriceQuantity(bool useRowMajor = true);            // O(n×m)
    void displayPriceQuantityTable(bool useRowMajor = true);      // O(n×m)
    
    // Sparse matrix operations
    void optimizeSparseStorage(int threshold = 10);               // O(n)
    void displaySparseItems();                                    // O(k)
    
    // Utility methods
    void displayAllItems();                                       // O(n)
    void displayComplexityAnalysis();                             // O(1)
    int getItemCount() const { return itemCount; }
};

#endif // INVENTORY_SYSTEM_H