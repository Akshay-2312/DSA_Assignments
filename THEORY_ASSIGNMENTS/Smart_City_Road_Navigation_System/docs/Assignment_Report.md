# Assignment Report: Smart City Road Navigation System

## Road Network ADT
- NodeID: unique ID for intersections/zones
- NodeName: human-readable name
- Connections: weighted edges (list and matrix)
- ZoneDetails: description (residential, commercial, etc.)
- Methods: insertNode, addEdge, findShortestPath, organizeZones

## Graph Representation Strategy
- Adjacency List: efficient for sparse graphs and used by Dijkstra/Prim
- Adjacency Matrix: used by Floyd–Warshall (dense-friendly, O(1) lookup)

## Shortest Path Algorithms
- Dijkstra: single-source shortest path via priority queue; complexity O(E log V)
- Floyd–Warshall: all-pairs shortest paths; complexity O(V³)

## Trees & Zone Indexing
- Binary Tree: simple hierarchical insertion by name
- AVL Tree: self-balancing for O(log n) operations; used for efficient indexing

## Topological Sort
- Kahn’s algorithm over directed construction graph (DAG)
- Determines order for one-way road construction without cycles

## MST (Prim)
- Prim’s algorithm builds cost-efficient road network layout on undirected graph
- Complexity O(E log V) using priority queue

## Efficiency Analysis
- See `Complexity_Analysis.md` for detailed tables and asymptotics

## Screenshots
- Generated outputs should be saved into `screenshots/`

## Conclusion & Learning Outcomes
- Demonstrated applied graph theory in navigation and planning
- Compared shortest path strategies (single-source vs all-pairs)
- Used AVL/Binary trees for efficient zone indexing
- Applied topological sorting for construction scheduling
- Built MST for economical infrastructure design