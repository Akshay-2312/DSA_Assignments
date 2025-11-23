# Complexity Analysis for Grocery Inventory Management System

## Time and Space Complexity Analysis

| Operation | Description | Time Complexity | Space Complexity |
|-----------|-------------|----------------|------------------|
| insertItem() | Add new item to array | O(1) amortized | O(1) |
| deleteItem() | Remove item by ID | O(n) | O(1) |
| searchItem() | Search by name or ID | O(n) | O(1) |
| managePriceQuantity() | Row/column traversal | O(n×m) | O(1) |
| optimizeSparseStorage() | Convert low-quantity items | O(n) | O(k) |

## Detailed Analysis

### 1. insertItem() / addItemRecord()
- **Time Complexity**: O(1) amortized
  - Adding an item to the end of the array is a constant-time operation
  - Checking for duplicate IDs requires O(n) in worst case
  - Amortized analysis considers the average case over multiple operations
- **Space Complexity**: O(1)
  - Only requires fixed additional space regardless of input size

### 2. deleteItem() / removeItemRecord()
- **Time Complexity**: O(n)
  - Finding the item to delete requires O(n) in worst case
  - Shifting elements to fill the gap requires O(n) in worst case
- **Space Complexity**: O(1)
  - Only requires fixed additional space regardless of input size

### 3. searchItem() / searchByItem()
- **Time Complexity**: O(n)
  - Linear search through the array requires O(n) in worst case
  - Searching in sparse items (map) is O(log k) where k is the number of sparse items
  - Overall complexity is dominated by the array search: O(n)
- **Space Complexity**: O(1)
  - Only requires fixed additional space regardless of input size

### 4. managePriceQuantity()
- **Time Complexity**: O(n×m)
  - Traversing the 2D array requires visiting all n×m elements
  - Row-major and column-major orders have the same asymptotic complexity
- **Space Complexity**: O(1)
  - Only requires fixed additional space regardless of input size

### 5. optimizeSparseStorage()
- **Time Complexity**: O(n)
  - Scanning all items to find low-quantity ones requires O(n)
  - Adding to the sparse map is O(log k) per item, but dominated by O(n)
- **Space Complexity**: O(k)
  - Where k is the number of sparse items (low-quantity items)
  - In worst case, k could be equal to n (all items are sparse)

## Variables
- n = number of items in inventory
- m = size of price/quantity table (rows × columns)
- k = number of sparse items (low-quantity items)

## Memory Usage Analysis
- 1D Array (itemArray): O(n) space
- 2D Array (priceQuantityTable): O(r×c) space where r = rows, c = columns
- Sparse Matrix (map): O(k) space where k = number of sparse items

## Optimization Strategies
1. **Sparse Matrix Representation**: Reduces memory usage for low-quantity items
2. **Row-Major vs Column-Major**: Demonstrates memory access patterns for 2D arrays
3. **Amortized Operations**: Balances performance across multiple operations