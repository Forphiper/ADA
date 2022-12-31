#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct edge_data {
	int vertex;
	long long len;
};

// min heap comparator
class pqComparator {
public:
	bool operator() (const edge_data& a, const edge_data& b) {
		return a.len > b.len;
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
	
	long long mst_weight = 0;
	
	// start from point 0
	priority_queue<edge_data, vector<edge_data>, pqComparator> pq;
	pq.push({0, 0});
	len_keys[0] = 0;
	
	while(!pq.empty()) {
		edge_data curr_edge = pq.top();
		pq.pop();
		
		int u = curr_edge.vertex;
		
		if(is_vertex_in_mst[u]) {
			continue;
		}
		
		is_vertex_in_mst[u] = true;
		
		mst_weight += curr_edge.len;
		
		for(auto& edge_of_u : adjacency[u]) {
			int v = edge_of_u.vertex;
			long long uv_len = edge_of_u.len;
			
			if(!is_vertex_in_mst[v]) {
				if(uv_len < len_keys[v]) {
					len_keys[v] = uv_len;
					pq.push({v, uv_len});
				}
			}
		}
	}
	cout << mst_weight << '\n';
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
	
	int ai, bi;
	long long ci;
	for(int i = 0; i < graph.edge_num; i++) {
		cin >> ai >> bi >> ci;
		
		graph.adjacency[ai - 1].push_back({bi - 1, ci});
		graph.adjacency[bi - 1].push_back({ai - 1, ci});
	}
	
	graph.primMST();
	
	return 0;
}
