#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// min heap comparator
class pqComparator {
public:
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
		return a.second > b.second;
	}
};

class Graph {
public:
	int cities;
	int roads;
	vector<pair<int, int>>* adj;
	
	Graph(int N, int M);
	long long getSumOfShortestDist(int src);
	void setOneEdgeZero();
	~Graph();
};

Graph::Graph(int N, int M) {
	cities = N;
	roads = M;
	adj = new vector<pair<int, int>>[N];
}

long long Graph::getSumOfShortestDist(int src) {
	// Dijkstra using priority_queue
	priority_queue<pair<int, int>, vector<pair<int, int>>, pqComparator> pq;
	vector<long long> distances(cities, LLONG_MAX);
	
	pq.push(make_pair(src, 0));
	distances[src] = 0;
	
	while(!pq.empty()) {
		int u = pq.top().first;
		pq.pop();
		
		for(pair<int, int>& neighbor : adj[u]) {
			int v = neighbor.first;
			int weight = neighbor.second;
			
			if(distances[v] > distances[u] + weight) {
				distances[v] = distances[u] + weight;
				pq.push(make_pair(v, distances[v]));
			}
		}
	}
	
	long long sum_of_dist = 0;
	for(long long dist : distances) {
		sum_of_dist += dist;
	}
	return sum_of_dist;
}

void Graph::setOneEdgeZero() {
	long long min_sum_of_dist = LLONG_MAX;
	long long sum_of_dist;
	for(int i = 1; i  < cities; i++) {
		adj[0].push_back(make_pair(i, 0));
		sum_of_dist = getSumOfShortestDist(0);
		min_sum_of_dist = min(min_sum_of_dist, sum_of_dist);
		adj[0].pop_back();
	}
	cout << min_sum_of_dist << '\n';
}


Graph::~Graph() {
	delete[] adj;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int N;
	int M;
	cin >> N >> M;
	Graph graph(N, M);
	
	int ai, bi, ci;
	for(int i = 0; i < graph.roads; i++) {
		cin >> ai >> bi >> ci;
		graph.adj[ai - 1].push_back(make_pair(bi - 1, ci));
	}
	
	graph.setOneEdgeZero();
	
	return 0;
}
