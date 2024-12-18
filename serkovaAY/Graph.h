#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include "Station.h"
#include "GasSupplySystem.h"

class Station;
struct Edge;

class Graph
{
public:

	void DFS(std::vector<bool>& visited, int vertex, std::stack<int>& result);
	std::vector<int> TopologicalSorting();
	bool isDAG();

	Graph(std::unordered_map<int, Station>& cs_objects,
		std::unordered_map<int, Edge>& connections);

private:
	bool hasCycleUtil(int vertex, std::vector<bool>& visited,
		std::vector<bool>& recursion_stack);

	std::vector<std::vector<int>> adjacency_matrix;
	std::unordered_map<int, int> stations_ids;
	int num_vertexes;
};
