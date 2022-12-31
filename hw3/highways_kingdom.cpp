#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct edge_data {
	int vertex;
	long long len;
	long long total_cost;
};

// min heap comparator
class pqComparator {
public:
	bool operator() (const edge_data& a, const edge_data& b) {
		if(a.len > b.len) return true;
		if(a.len < b.len) return false;
		
		return a.total_cost > b.total_cost;
	}
};

class Graph {
public:
	int vertex_num;
	int edge_num;
	vector<edge_data>* adjacency;
	
	long long* len_keys;
	bool* is_vertex_in_mst;
	
	Graph(int n, int m);
	void primMST();
	~Graph();
};

Graph::Graph(int n, int m) {
	vertex_num = n;
	edge_num = m;
	adjacency = new vector<edge_data>[n];
	len_keys = new long long[n];
	is_vertex_in_mst = new bool[n];
}

void Graph::primMST() {
	// initialize
	for(int i = 0; i < vertex_num; i++) {
		len_keys[i] = LLONG_MAX;
		is_vertex_in_mst[i] = false;
	}
	
	long long all_vertex_total_cost = 0;
	vector<long long> curr_max_lens(vertex_num, 0);
	vector<long long> curr_total_costs(vertex_num, 0);
	
	// start from point 0
	priority_queue<edge_data, vector<edge_data>, pqComparator> pq;
	pq.push({0, 0, 0});
	len_keys[0] = 0;
	
	while(!pq.empty()) {
		edge_data curr_edge = pq.top();
		pq.pop();
		
		int u = curr_edge.vertex;
		
		if(is_vertex_in_mst[u]) {
			continue;
		}
		
		is_vertex_in_mst[u] = true;
		
		all_vertex_total_cost += curr_edge.total_cost;
		curr_total_costs[u] = curr_edge.total_cost;
		
		for(auto& edge_of_u : adjacency[u]) {
			int v = edge_of_u.vertex;
			long long uv_len = edge_of_u.len;
			long long uv_cost = edge_of_u.total_cost;
			
			long long curr_cost;
			if(!is_vertex_in_mst[v]) {
				if(uv_len < len_keys[v]) {
					len_keys[v] = uv_len;
					
					if(uv_len > curr_max_lens[u]) {
						curr_max_lens[v] = uv_len;
						curr_cost = uv_cost;
					}
					else if(uv_len == curr_max_lens[u]) {
						curr_max_lens[v] = uv_len;
						curr_cost = curr_total_costs[u] + uv_cost;
					}
					else if(uv_len < curr_max_lens[u]) {
						curr_max_lens[v] = curr_max_lens[u];
						curr_cost = curr_total_costs[u];
					}
					pq.push({v, uv_len, curr_cost});
				}
				else if(uv_len == len_keys[v]) {
					if(uv_len > curr_max_lens[u]) {
						curr_cost = uv_cost;
					}
					else if(uv_len == curr_max_lens[u]) {
						curr_cost = curr_total_costs[u] + uv_cost;
					}
					else if(uv_len < curr_max_lens[u]) {
						curr_cost = curr_total_costs[u];
					}
					pq.push({v, uv_len, curr_cost});
				}
			}
		}
	}
	cout << all_vertex_total_cost << '\n';
}


Graph::~Graph() {
	delete[] adjacency;
	delete[] len_keys;
	delete[] is_vertex_in_mst;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;
	Graph graph(n, m);
	
	int ui, vi;
	long long li, ci;
	for(int i = 0; i < graph.edge_num; i++) {
		cin >> ui >> vi >> li >> ci;
		
		graph.adjacency[ui].push_back({vi, li, ci});
		graph.adjacency[vi].push_back({ui, li, ci});
	}
	
	graph.primMST();
	
	return 0;
}
