# Campus Navigation and Utility Planner

## Overview
This project implements a Campus Navigation and Utility Planner system that helps manage campus buildings, find optimal navigation paths between buildings, plan utility cable layouts, and calculate energy costs. The system uses various data structures and algorithms including Binary Search Trees (BST), AVL Trees, Graphs, Dijkstra's Algorithm, Kruskal's Algorithm, and Expression Trees.

## Features
- Building management with BST/AVL Tree for efficient storage and retrieval
- Campus navigation using Dijkstra's Algorithm for shortest paths
- Utility cable layout planning using Kruskal's Algorithm for minimum spanning trees
- Energy bill calculation using Expression Trees
- Tree traversals (Inorder, Preorder, Postorder) for listing campus buildings

## Data Structures and Algorithms
- **Binary Search Tree (BST)**: For storing and retrieving building records
- **AVL Tree**: Self-balancing BST for optimized retrieval operations
- **Graph**: Represented using both Adjacency Matrix and Adjacency List
- **Dijkstra's Algorithm**: For finding the shortest path between buildings
- **Kruskal's Algorithm**: For finding the minimum spanning tree for utility cable layout
- **Expression Tree**: For evaluating arithmetic expressions for energy bill calculations

## Time and Space Complexity Analysis

| Operation | Algorithm / Structure | Time Complexity | Space Complexity |
|-----------|----------------------|-----------------|------------------|
| insertBuilding() | BST Insertion | O(h) (O(log n) for AVL) | O(n) |
| traverseBuildings() | DFS Traversal | O(n) | O(h) |
| constructCampusGraph() | Graph Build (Adj. List) | O(V + E) | O(V + E) |
| findOptimalPath() | Dijkstra's Algorithm | O(E log V) (with priority queue) | O(V + E) |
| planUtilityLayout() | Kruskal's Algorithm | O(E log V) | O(V + E) |
| evaluateExpression() | Expression Tree Evaluation | O(n) | O(h) |

## Compilation and Execution
To compile and run the program:

```bash
# Navigate to the src directory
cd src

# Compile the program
g++ -std=c++11 main.cpp -o campus_planner

# Run the program
./campus_planner
```

## Usage
The program provides a menu-driven interface with the following options:
1. Add New Building Record
2. List Campus Buildings (Inorder/Preorder/Postorder)
3. Construct Campus Graph
4. Find Optimal Navigation Path (Dijkstra)
5. Plan Utility Cable Layout (Kruskal)
6. Evaluate Energy Bill (Expression Tree)
7. Exit

## Project Structure
```
📦 Lab_Assignment_4_Campus_Navigation_and_Utility_Planner/
│
├── 📁 src/
│   ├── main.cpp                   # Main menu-driven program
│   ├── BuildingADT.h              # ADT class for building
│   ├── Tree.h                     # BST + AVL implementation
│   ├── Graph.h                    # Graph representation (Matrix + List)
│   ├── Dijkstra.h                 # Shortest path algorithm
│   ├── Kruskal.h                  # Minimum spanning tree
│   ├── ExpressionTree.h           # Expression tree for bill evaluation
│
├── 📁 reports/
│   ├── Implementation_Report.pdf  # Full write-up of design
│   ├── Complexity_Analysis.pdf    # Time & space complexity table
│
├── 📁 screenshots/
│   ├── output_traversal.png
│   ├── output_dijkstra.png
│   ├── output_kruskal.png
│   ├── output_expression.png
│
└── README.md                      # This file
```

## Author
[Akshay yadav]
[2401730129]
[Data Structures]

## License
This project is licensed under the MIT License - see the LICENSE file for details.
