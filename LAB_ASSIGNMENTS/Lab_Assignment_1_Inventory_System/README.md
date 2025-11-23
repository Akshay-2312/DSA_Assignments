# Grocery Inventory Management System

## Overview
This project implements a Grocery Inventory Management System using arrays, multi-dimensional data storage, and sparse matrix optimization. The system allows for efficient management of grocery items with features for adding, deleting, searching, and optimizing storage for low-quantity items.

## Features
- Add, delete, and search inventory items
- Display all items with their details
- Manage price/quantity relationships using 2D arrays
- Demonstrate row-major vs column-major order traversals
- Optimize storage for rarely restocked items using sparse matrix representation
- Display time and space complexity analysis for all operations

## Data Structures Used
- 1D Array: For storing inventory items
- 2D Array: For price/quantity relationships
- Map: For sparse representation of low-quantity items

## Setup and Compilation
1. Ensure you have a C++ compiler (supporting C++11 or later)
2. Navigate to the project directory
3. Compile the project:
   ```
   g++ -std=c++11 src/main.cpp src/InventorySystem.cpp -o inventory_system
   ```
4. Run the executable:
   ```
   ./inventory_system
   ```

## Directory Structure
```
Lab_Assignment_1_Inventory_System/
│
├── src/
│   ├── main.cpp                # Main executable file with menu-driven system
│   ├── InventoryItem.h         # Header file for ADT class
│   ├── InventorySystem.h       # Header for system management class
│   └── InventorySystem.cpp     # Implementation file
│
├── reports/
│   ├── Complexity_Analysis.pdf # Time & space analysis for each function
│   ├── Implementation_Report.pdf # Explanation of design & outputs
│
├── screenshots/
│   ├── output_insert.png
│   ├── output_search.png
│   ├── output_sparse.png
│   └── output_complexity.png
│
└── README.md                   # This file
```

## Author
[Akshay yadav]
[2401730129]
[Data Structures]

## License
This project is for educational purposes only.
