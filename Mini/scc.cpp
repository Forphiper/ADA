#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
public:
	int vertices;
	vector<vector<int>> adj;
	vector<vector<int>> adj_transpose;
	vector<bool> visited;
	stack<int> stk;
	long long curr_component_size;
	
	Graph(int V);
	void firstDFS(int v);
	void setTranspose();
	void secondDFS(int v);
	void scc();
	~Graph();
};

Graph::Graph(int V)
{
    vertices = V;
    adj.resize(V);
    adj_transpose.resize(V);
    visited.resize(V);
}

void Graph::firstDFS(int v)
{
	visited[v] = true;
	for(int neighbor : adj[v]) {
		if(!visited[neighbor]) {
			firstDFS(neighbor);
		}
	}
	stk.push(v);
}

void Graph::setTranspose()
{
	for(int i = 0; i < vertices; i++) {
		for(int neighbor : adj[i]) {
			adj_transpose[neighbor].push_back(i);
		}
	}
}

void Graph::secondDFS(int v)
{
	visited[v] = true;
	curr_component_size++;
	
	for(int neighbor : adj_transpose[v]) {
		if(!visited[neighbor]) {
			secondDFS(neighbor);
		}
	}
}

void Graph::scc()
{
	fill(visited.begin(), visited.end(), false);
	for(int i = 0; i < vertices; i++) {
		if(!visited[i]) {
			firstDFS(i);
		}
	}
	
	setTranspose();
	fill(visited.begin(), visited.end(), false);
	long long num_of_pairs = 0;
	while(!stk.empty()) {
		int v = stk.top();
		stk.pop();
		
		if(!visited[v]) {
			curr_component_size = 0;
			secondDFS(v);
			num_of_pairs += curr_component_size * (curr_component_size - 1) / 2;
		}
	}
	cout << num_of_pairs << '\n';
}

Graph::~Graph() {}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int V, E;
	cin >> V >> E;
	Graph graph(V);
	
	int u, v;
	for(int i = 0; i < E; i++) {
		cin >> u >> v;
		graph.adj[u - 1].push_back(v - 1);
	}
	
	graph.scc();
	
	return 0;
}
