#include "ypglpk.hpp"
#include <iostream>

using namespace std;

struct edge_data {
	int vertex;
	int order;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ypglpk::set_output(false);
	
	int V, E;
	cin >> V >> E;
	
	vector<vector<edge_data>> adj_out(V);
	vector<vector<edge_data>> adj_in(V);
		
	vector<vector<double>> A(3 * V + E, vector<double>(E + V));
	// 3V + E constraints
	vector<double> b(3 * V + E);
	// E + V variables
	vector<double> c(E + V);
	vector<int> vartype(E + V);
	
	int ui, vi;
	double wi;
	for(int i = 0; i < E; i++) {
		cin >> ui >> vi >> wi;
		adj_out[ui - 1].push_back({vi - 1, i});
		adj_in[vi - 1].push_back({ui - 1, i});
		
		// maximize w_i,j * x_i,j
		c[i] = wi;
	}
	
	// binary value: 0 or 1
	for(int i = 0; i < E; i++) {
		vartype[i] = GLP_BV;
	}
	// integer value
	for(int i = 0; i < V; i++) {
		vartype[E + i] = GLP_IV;
	}
	
	// first constraint:
	// flow-in equals flow-out, except for src and dest
	// for src, flow-out - flow-in = 1
	// for dest, flow-in - flow-out = 1
	for(int i = 0; i < V; i++) {
		// use 2 '<=' to implement '='
		for(auto& edge : adj_out[i]) {
			A[i][edge.order] = 1;
			A[V + i][edge.order] = -1;
		}
		for(auto& edge : adj_in[i]) {
			A[i][edge.order] = -1;
			A[V + i][edge.order] = 1;
		}
		if(i == 0) {
			b[i] = 1;
			b[V + i] = -1;
		}
		else if(i == V - 1) {
			b[i] = -1;
			b[V + i] = 1;
		}
		else {
			b[i] = 0;
			b[V + i] = 0;
		} 
	}
	
	// second constraint: 
	// outflow of each node <= 1, except for dest
	// for dest, outflow = 0
	for(int i = 0; i < V; i++) {
		for(auto& edge : adj_out[i]) {
			A[2 * V + i][edge.order] = 1;
		}
		b[2 * V + i] = (i == V - 1)? 0 : 1;
	}
	
	// third constraint:
	// Miller-Tucker-Zemlin
	int edge_count = 0;
	for(int i = 0; i < V; i++) {
		for(auto& edge : adj_out[i]) {
			A[3 * V + edge_count][edge.order] = 10000;
			A[3 * V + edge_count][E + i] = 1;
			A[3 * V + edge_count][E + edge.vertex] = -1;
			b[3 * V + edge_count] = 9999;
			edge_count++;
		}
	}
	
	pair<double, vector<double>> res;
	res = ypglpk::mixed_integer_linear_programming(A, b, c, vartype);
    
    if(res.first == -ypglpk::INF) { // cant find the path
        cout << "-1";
    }
    else {
		cout << (long long)res.first << '\n';
		string edge_in_path;
		for(int i = 0; i < E; i++) {
			edge_in_path += (res.second[i] == 1)? '1' : '0';
		}
		cout << edge_in_path << '\n';
    }
    
    return 0;
}

