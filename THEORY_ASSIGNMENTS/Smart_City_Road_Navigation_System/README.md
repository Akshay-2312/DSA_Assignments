# Smart City Road Navigation System

## Overview
This project implements a Smart City Road Navigation System featuring:
- Graphs with both adjacency list and adjacency matrix
- Shortest path algorithms (Dijkstra and Floyd–Warshall)
- Trees (Binary Tree and AVL Tree) for zone indexing
- Topological Sort for road construction priority (DAG)
- Minimum Spanning Tree (Prim) for cost-efficient layout

## Features
- Add and manage zones and roads
- Compute single-source shortest paths (Dijkstra)
- Compute all-pairs shortest paths (Floyd–Warshall)
- Index zones using Binary and AVL trees with traversals
- Determine construction order via Topological Sort
- Generate MST using Prim's algorithm

## Build & Run
Navigate to `src` and compile:

```
g++ -std=c++17 main.cpp -o smart_city
./smart_city
```

## Project Structure
```
📦 Smart_City_Road_Navigation_System/
├── 📁 src/
│   ├── main.cpp
│   ├── Graph.h
│   ├── Dijkstra.h
│   ├── FloydWarshall.h
│   ├── Tree.h
│   ├── TopologicalSort.h
│   ├── MST.h
│   ├── Utils.h
├── 📁 docs/
│   ├── Assignment_Report.md
│   ├── Complexity_Analysis.md
│   ├── ADT_Design.md
├── 📁 data/
│   ├── input_graph.txt
│   ├── zone_details.txt
├── 📁 screenshots/
│   ├── .gitkeep
└── README.md
```

## Notes
- The `docs/*.md` files can be exported to PDF for submission.
- Sample inputs are provided under `data/`.