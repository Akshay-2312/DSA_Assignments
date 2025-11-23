# Implementation Report: Campus Navigation and Utility Planner

## 1. Introduction

This report details the implementation of the Campus Navigation and Utility Planner system, which provides functionality for managing campus buildings, finding optimal navigation paths, planning utility cable layouts, and calculating energy costs. The system is built using various data structures and algorithms including Binary Search Trees (BST), AVL Trees, Graphs, Dijkstra's Algorithm, Kruskal's Algorithm, and Expression Trees.

## 2. System Architecture

The system is organized into several modular components:

### 2.1 Building ADT
- Implemented in `BuildingADT.h`
- Represents a campus building with attributes such as ID, name, location, and connections
- Provides methods for managing building connections and displaying information

### 2.2 Tree Structures
- Implemented in `Tree.h`
- Includes both BST and AVL tree implementations
- Used for efficient storage and retrieval of building records
- Supports various traversal methods (inorder, preorder, postorder, level order)

### 2.3 Graph Representation
- Implemented in `Graph.h`
- Supports both adjacency matrix and adjacency list representations
- Used for representing the campus layout and connections between buildings

### 2.4 Pathfinding Algorithm
- Implemented in `Dijkstra.h`
- Uses Dijkstra's algorithm to find the shortest path between buildings
- Provides methods for calculating and displaying the optimal navigation path

### 2.5 Minimum Spanning Tree
- Implemented in `Kruskal.h`
- Uses Kruskal's algorithm to find the minimum spanning tree
- Used for planning utility cable layouts to minimize total cable length

### 2.6 Expression Evaluation
- Implemented in `ExpressionTree.h`
- Uses an expression tree to evaluate arithmetic expressions
- Used for calculating energy bills based on user-provided formulas

### 2.7 Main Interface
- Implemented in `main.cpp`
- Provides a menu-driven interface for user interaction
- Integrates all components into a cohesive system

## 3. Implementation Details

### 3.1 Building ADT
The `Building` class is designed to store information about campus buildings:
- Each building has a unique ID, name, and (x,y) location coordinates
- Buildings maintain a list of connections to other buildings
- Comparison operators are overloaded to enable sorting and searching in tree structures

### 3.2 Tree Structures
Two tree implementations are provided:
- `BST`: A standard binary search tree with basic operations
- `AVLTree`: A self-balancing binary search tree that extends the BST class
  - Implements rotations to maintain balance
  - Ensures O(log n) time complexity for operations

### 3.3 Graph Representation
The `Graph` class supports two representations:
- Adjacency Matrix: A 2D array where matrix[i][j] represents the distance between buildings i and j
- Adjacency List: A vector of vectors where each entry contains connected buildings and distances
- The class provides methods to convert between building IDs and internal indices

### 3.4 Dijkstra's Algorithm
The `Dijkstra` class implements the shortest path algorithm:
- Uses a priority queue to efficiently select the next vertex
- Maintains distance and predecessor arrays
- Provides methods to reconstruct and display the shortest path

### 3.5 Kruskal's Algorithm
The `Kruskal` class implements the minimum spanning tree algorithm:
- Uses a disjoint-set data structure to detect cycles
- Sorts edges by weight to process them in ascending order
- Builds the MST by adding edges that don't create cycles

### 3.6 Expression Tree
The `ExpressionTree` class evaluates arithmetic expressions:
- Converts infix expressions to postfix notation
- Builds a binary tree from the postfix expression
- Recursively evaluates the expression tree

### 3.7 Main Interface
The main program provides a user-friendly interface:
- Displays a menu of available operations
- Handles user input and validation
- Calls appropriate methods from other components based on user selection

## 4. Design Decisions and Justifications

### 4.1 Use of AVL Trees
- AVL trees were chosen over regular BSTs to ensure O(log n) time complexity for operations
- This is particularly important for large campuses with many buildings
- The self-balancing property prevents performance degradation in worst-case scenarios

### 4.2 Dual Graph Representation
- Both adjacency matrix and list representations are implemented to demonstrate their differences
- Adjacency matrix provides O(1) edge lookup but requires O(V²) space
- Adjacency list is more space-efficient for sparse graphs and better suited for Dijkstra's algorithm

### 4.3 Dijkstra's Algorithm Implementation
- A priority queue-based implementation was chosen for its efficiency
- This reduces the time complexity from O(V²) to O(E log V)
- The algorithm is well-suited for finding shortest paths in a campus setting

### 4.4 Kruskal's Algorithm for MST
- Kruskal's algorithm was selected for its simplicity and efficiency
- The disjoint-set data structure provides efficient cycle detection
- The algorithm is ideal for planning utility layouts to minimize total cable length

### 4.5 Expression Tree for Calculations
- Expression trees provide a flexible way to evaluate complex formulas
- The implementation supports variables, allowing for customizable energy bill calculations
- The tree structure makes the evaluation process intuitive and extensible

## 5. Challenges and Solutions

### 5.1 Graph Representation
- **Challenge**: Efficiently mapping between building IDs and internal graph indices
- **Solution**: Implemented mapping functions and maintained a vector of building pointers

### 5.2 AVL Tree Balancing
- **Challenge**: Ensuring correct balance factor calculation and rotation implementation
- **Solution**: Carefully implemented height update methods and rotation operations

### 5.3 Expression Evaluation
- **Challenge**: Parsing and evaluating complex arithmetic expressions
- **Solution**: Implemented a two-step process: infix to postfix conversion followed by tree construction

### 5.4 Path Reconstruction
- **Challenge**: Reconstructing the shortest path from Dijkstra's algorithm results
- **Solution**: Maintained a predecessor array and implemented a recursive path reconstruction method

## 6. Future Improvements

### 6.1 User Interface Enhancements
- Implement a graphical user interface to visualize the campus map
- Add interactive features for selecting buildings and viewing paths

### 6.2 Additional Algorithms
- Implement A* algorithm as an alternative to Dijkstra's for pathfinding
- Add Prim's algorithm as an alternative to Kruskal's for MST construction

### 6.3 Performance Optimizations
- Optimize memory usage for large campus graphs
- Implement more efficient data structures for specific operations

### 6.4 Additional Features
- Add support for building categories and filtering
- Implement time-dependent pathfinding for different times of day
- Add support for multi-criteria optimization (distance, time, accessibility)

## 7. Conclusion

The Campus Navigation and Utility Planner system successfully implements the required functionality using appropriate data structures and algorithms. The modular design allows for easy maintenance and extension, while the efficient implementations ensure good performance even for large campuses. The system provides a solid foundation for campus navigation and utility planning, with potential for further enhancements in the future.