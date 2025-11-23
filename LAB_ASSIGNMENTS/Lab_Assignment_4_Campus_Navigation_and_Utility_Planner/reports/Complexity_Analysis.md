# Complexity Analysis: Campus Navigation and Utility Planner

## Time and Space Complexity Analysis

This document provides a detailed analysis of the time and space complexity for each major operation in the Campus Navigation and Utility Planner system.

### 1. Building ADT Operations

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Constructor | O(1) | O(1) | Basic initialization |
| Add Connection | O(1) | O(1) | Adding to vector |
| Get Connections | O(1) | O(1) | Returning reference |
| Display Info | O(n) | O(1) | n = number of connections |

### 2. Tree Operations

#### 2.1 Binary Search Tree (BST)

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Insert | O(h) | O(h) | h = height of tree (worst case O(n)) |
| Search | O(h) | O(h) | Recursive stack space |
| Delete | O(h) | O(h) | Recursive stack space |
| Inorder Traversal | O(n) | O(h) | Recursive stack space |
| Preorder Traversal | O(n) | O(h) | Recursive stack space |
| Postorder Traversal | O(n) | O(h) | Recursive stack space |
| Level Order Traversal | O(n) | O(n) | Queue space for BFS |

#### 2.2 AVL Tree

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Insert | O(log n) | O(log n) | Self-balancing ensures logarithmic height |
| Search | O(log n) | O(log n) | Recursive stack space |
| Delete | O(log n) | O(log n) | Recursive stack space |
| Rotation | O(1) | O(1) | Constant time operation |
| Height Update | O(1) | O(1) | Constant time operation |
| Balance Factor | O(1) | O(1) | Constant time operation |

### 3. Graph Operations

#### 3.1 Adjacency Matrix Representation

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Add Vertex | O(V) | O(V) | Resize matrix |
| Add Edge | O(1) | O(1) | Direct access |
| Get Edge | O(1) | O(1) | Direct access |
| Get All Edges | O(V²) | O(1) | Traverse entire matrix |
| Memory Usage | - | O(V²) | V = number of vertices |

#### 3.2 Adjacency List Representation

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Add Vertex | O(1) | O(1) | Add to vector |
| Add Edge | O(1) | O(1) | Add to vector |
| Get Edge | O(E/V) | O(1) | Average case, E = edges, V = vertices |
| Get All Edges | O(V + E) | O(1) | Traverse all lists |
| Memory Usage | - | O(V + E) | More efficient for sparse graphs |

### 4. Dijkstra's Algorithm

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Find Shortest Path | O(E log V) | O(V) | Using priority queue |
| Without Priority Queue | O(V²) | O(V) | Simple implementation |
| Path Reconstruction | O(V) | O(V) | Trace predecessors |
| Display Path | O(P) | O(P) | P = path length |

### 5. Kruskal's Algorithm

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Sort Edges | O(E log E) | O(E) | Sorting by weight |
| Find MST | O(E log V) | O(V + E) | Using disjoint-set |
| Disjoint-Set Operations | O(α(n)) | O(V) | α = inverse Ackermann function (nearly constant) |
| Display MST | O(V) | O(V) | V-1 edges in MST |

### 6. Expression Tree

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Infix to Postfix | O(n) | O(n) | n = expression length |
| Build Tree | O(n) | O(n) | From postfix expression |
| Evaluate Tree | O(n) | O(h) | h = tree height (recursive stack) |
| Display Expression | O(n) | O(h) | Inorder traversal |

### 7. Overall System Performance

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Add Building | O(log n) | O(log n) | AVL tree insertion |
| List Buildings | O(n) | O(log n) | Tree traversal |
| Construct Graph | O(V + E) | O(V + E) | Building adjacency list |
| Find Path | O(E log V) | O(V) | Dijkstra's algorithm |
| Plan Layout | O(E log E) | O(V + E) | Kruskal's algorithm |
| Evaluate Bill | O(n) | O(n) | Expression tree |

## Asymptotic Analysis Summary

### Best Case Scenarios
- Building insertion: O(log n) with AVL tree (balanced)
- Path finding: O(E + V log V) with optimized Dijkstra's
- MST construction: O(E log V) with efficient disjoint-set

### Worst Case Scenarios
- Building insertion: O(n) if using unbalanced BST
- Path finding: O(V²) without priority queue
- Graph operations: O(V²) with dense graphs

### Space Efficiency
- Adjacency List: O(V + E) - efficient for sparse campus graphs
- Adjacency Matrix: O(V²) - less efficient for large campuses
- AVL Tree: O(n) - efficient storage of building records

## Optimization Opportunities

1. **Priority Queue Implementation**: Using a Fibonacci heap could improve Dijkstra's algorithm to O(E + V log V)

2. **Graph Representation**: For very sparse graphs, consider specialized sparse matrix representations

3. **Expression Evaluation**: Compile expressions to reduce repeated parsing

4. **Parallel Processing**: Some operations like MST construction could benefit from parallelization

## Conclusion

The implemented data structures and algorithms provide efficient solutions for the Campus Navigation and Utility Planner system. The use of AVL trees ensures logarithmic time complexity for building operations, while Dijkstra's and Kruskal's algorithms provide efficient solutions for pathfinding and utility planning respectively. The space complexity is kept reasonable through appropriate data structure choices, particularly the use of adjacency lists for sparse campus graphs.