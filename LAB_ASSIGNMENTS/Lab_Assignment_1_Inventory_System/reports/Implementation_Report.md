# Implementation Report: Grocery Inventory Management System

## 1. Introduction

The Grocery Inventory Management System is designed to efficiently manage inventory items in a grocery store. It implements array-based data structures, demonstrates memory layout concepts through row-major and column-major ordering, and optimizes storage for rarely restocked items using sparse matrix representation.

## 2. InventoryItem ADT Design

### Attributes
- **ItemID** (int): Unique identifier for each item
- **ItemName** (string): Name of the grocery item
- **Quantity** (int): Number of items in stock
- **Price** (float): Price per item

### Methods
- **Constructors**: Default and parameterized constructors
- **Getters/Setters**: For all attributes
- **getTotalValue()**: Calculates total value (price × quantity)

## 3. Implementation Strategy

### Data Structures
1. **1D Array (itemArray)**
   - Primary storage for inventory items
   - Fixed-size array with dynamic item count

2. **2D Array (priceQuantityTable)**
   - Organizes price and quantity relationships
   - Demonstrates row-major and column-major traversal

3. **Sparse Matrix (sparseItems)**
   - Map-based representation for low-quantity items
   - Optimizes memory usage for rarely restocked products

### Memory Layout Approaches

#### Row-Major Order
- Elements are stored row by row
- Memory access pattern: (0,0), (0,1), (0,2), ..., (1,0), (1,1), ...
- Efficient for operations that process data row by row

#### Column-Major Order
- Elements are accessed column by column
- Memory access pattern: (0,0), (1,0), (2,0), ..., (0,1), (1,1), ...
- Demonstrates alternative memory traversal pattern

### Sparse Matrix Optimization
- Low-quantity items (below threshold) are moved to a map
- Reduces memory usage for rarely restocked products
- Provides efficient lookup by item ID

## 4. Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| insertItem() | O(1) amortized | O(1) |
| deleteItem() | O(n) | O(1) |
| searchItem() | O(n) | O(1) |
| managePriceQuantity() | O(n×m) | O(1) |
| optimizeSparseStorage() | O(n) | O(k) |

Where:
- n = number of items in inventory
- m = size of price/quantity table
- k = number of sparse items (low quantity)

## 5. Output Snapshots

### Adding Items
```
----- Add New Item -----
Enter Item ID: 101
Enter Item Name: Apples
Enter Quantity: 50
Enter Price: $1.99
Item added successfully.
```

### Searching Items
```
----- Search Item -----
1. Search by ID
2. Search by Name
Enter your choice: 1
Enter Item ID: 101

----- Item Found -----
ID: 101
Name: Apples
Quantity: 50
Price: $1.99
Total Value: $99.50
```

### Sparse Storage Optimization
```
Optimizing storage for items with quantity < 10...
Optimization complete. 2 items moved to sparse storage.

===== Sparse Storage Items (Low Quantity) =====
ID      Name                Quantity   Price     
------------------------------------------------
103     Mangoes             5          3.99      
105     Kiwi                8          2.50      
```

### Complexity Analysis Display
```
===== Complexity Analysis =====
Operation                 Time Complexity     Space Complexity   
-----------------------------------------------------------------
insertItem()              O(1) amortized      O(1)              
deleteItem()              O(n)                O(1)              
searchItem()              O(n)                O(1)              
managePriceQuantity()     O(n×m)              O(1)              
optimizeSparseStorage()   O(n)                O(k)              

Where:
  n = number of items in inventory
  m = size of price/quantity table
  k = number of sparse items (low quantity)
```

## 6. Conclusion

The Grocery Inventory Management System successfully implements array-based data structures with efficient operations for managing inventory items. The system demonstrates:

1. **Effective use of arrays** for storing and managing inventory data
2. **Memory layout concepts** through row-major and column-major traversals
3. **Storage optimization** using sparse matrix representation
4. **Complexity analysis** for all operations

The implementation provides a solid foundation for understanding array-based data structures and their performance characteristics. The sparse matrix optimization demonstrates how to efficiently handle special cases (low-quantity items) without sacrificing performance for common operations.