#include "Graph.h"

using namespace std;

void Graph::DFS(vector<bool>& visited,
	int vertex, stack<int>& result)
{
	visited[vertex] = true;
	int neighbor = 0;
	for (int adjacency : adjacency_matrix[vertex]) {
		if (!visited[neighbor] && adjacency == 1)
			DFS(visited, neighbor, result);
		neighbor++;
	}

	result.push(vertex);
}

vector<int> Graph::TopologicalSorting()
{
	vector<int> sorted_vertexes;
	vector<bool> visited(num_vertexes, false);
	stack<int> result_dfs;

	for (int vertex = 0; vertex < num_vertexes; vertex++) {
		if (!visited[vertex])
			DFS(visited, vertex, result_dfs);
	}

	vector<int> stations(stations_ids.size());
	for (auto& [id_cs, i] : stations_ids)
		stations[i] = id_cs;

	while (!result_dfs.empty()) {
		sorted_vertexes.push_back(stations[result_dfs.top()]);
		result_dfs.pop();
	}

	return sorted_vertexes;
}

bool Graph::hasCycleUtil(int vertex, vector<bool>& visited,
	vector<bool>& recursion_stack)
{
	visited[vertex] = true;
	recursion_stack[vertex] = true;

	for (int neighbor = 0; neighbor < num_vertexes; ++neighbor) {
		if (adjacency_matrix[vertex][neighbor] && !visited[neighbor]) {
			if (hasCycleUtil(neighbor, visited, recursion_stack)) {
				return true;  
			}
		}
		else if (adjacency_matrix[vertex][neighbor] && recursion_stack[neighbor]) {
			return true; 
		}
	}

	recursion_stack[vertex] = false;
	return false;
}

bool Graph::isDAG()
{
	std::vector<bool> visited(num_vertexes, false);
	std::vector<bool> recursion_stack(num_vertexes, false);

	for (int i = 0; i < num_vertexes; ++i) {
		if (!visited[i] && hasCycleUtil(i, visited, recursion_stack)) {
			return false;  
		}
	}

	return true;  
}

Graph::Graph(unordered_map<int, Station>& cs_objects,
	unordered_map<int, Edge>& connections)
{
	num_vertexes = cs_objects.size();

	adjacency_matrix.resize(num_vertexes);
	vector<int> row(num_vertexes, 0);
	for (int y = 0; y < num_vertexes; y++)
		adjacency_matrix[y] = row;

	int i = 0;
	for (auto& [id, cs] : cs_objects)
		stations_ids.insert({ id, i++ });

	for (auto& [id_pipe, edge] : connections)
		adjacency_matrix[stations_ids.at(edge.id_out)]
		[stations_ids.at(edge.id_in)] = 1;
}