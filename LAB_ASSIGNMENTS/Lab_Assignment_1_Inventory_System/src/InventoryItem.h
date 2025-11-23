#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>
using namespace std;

// InventoryItem ADT - Represents a single grocery item
class InventoryItem {
private:
    int itemID;
    string itemName;
    int quantity;
    float price;

public:
    // Default constructor
    InventoryItem() : itemID(0), itemName(""), quantity(0), price(0.0f) {}
    
    // Parameterized constructor
    InventoryItem(int id, const string& name, int qty, float p) 
        : itemID(id), itemName(name), quantity(qty), price(p) {}
    
    // Getters
    int getItemID() const { return itemID; }
    string getItemName() const { return itemName; }         
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    
    // Setters
    void setItemID(int id) { itemID = id; }
    void setItemName(const string& name) { itemName = name; }   
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(float p) { price = p; }
    
    // Calculate total value of this inventory item
    float getTotalValue() const { return price * quantity; }
};

#endif // INVENTORY_ITEM_H