# ADT Design: Road Network

## Zone (Node)

- id: int
- name: string
- details: string

## Graph

- directed: bool
- id_to_index: map<int,int>
- index_to_id: vector`<int>`
- zones: vector`<Zone>`
- adjList: vector<vector<pair<int,double>>>
- adjMatrix: vector<vector`<double>`>

### Operations

- addNode(id, name, details) -> index
- addEdge(fromId, toId, weight)
- getAdjList(), getAdjMatrix()
- getZoneById(id), getZoneByIndex(index)

## Trees

- ZoneBST: insert by name, traversals
- ZoneAVL: balanced insert by name

## Algorithms

- DijkstraSolver::shortestPath(graph, startId, endId)
- FloydWarshallSolver::solve(graph)
- TopologicalSorter::sortIds(graph)
- PrimMST::build(graph)
