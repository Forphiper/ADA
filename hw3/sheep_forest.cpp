#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

class Graph {
public:
	int vertices;
	int money;
	int* parents;
	vector<int>* childs;
	
	vector<vector<int>> forest;
	vector<int> tree_nodes;
	vector<int> root_of_each_tree;
	bool* dfs_visited;
	int* dfs_discover_time;
	int dfs_time_counter;
	int num_of_trees;
	
	long long* vertex_expenses;
	long long* tree_expenses;
	long long* tree_values;
	
	vector<vector<vector<long long>>> dp;
	
	Graph(int N, int M);
	void constructChilds();
	void dfsVisit(int v);
	void dfs();
	void calculateTreeValues();
	void dpEachTree();
	void dpMergeAllTrees();
	void constructDP();
	~Graph();
};

Graph::Graph(int N, int M) {
	vertices = N;
	money = M;
	parents = new int[N];
	childs = new vector<int>[N];
	
	dfs_visited = new bool[N];
	dfs_discover_time = new int[N];
	
	vertex_expenses = new long long[N];
	tree_expenses = new long long[N];
	tree_values = new long long[N];
}

void Graph::constructChilds() {
	for(int i = 0; i < vertices; i++) {
		int parent = parents[i];
		if(parent != -1) {
			childs[parent].push_back(i);
		}
	}
}

void Graph::dfsVisit(int v) {
	dfs_visited[v] = true;
	tree_nodes.push_back(v);
	dfs_time_counter++;
	dfs_discover_time[v] = dfs_time_counter;
	
	for(int child : childs[v]) {
		if(!dfs_visited[child]) {
			dfsVisit(child);
		}
	}
}

void Graph::dfs() {
	fill(dfs_visited, dfs_visited + vertices, false);
	dfs_time_counter = 0;
	
	for(int i = 0; i < vertices; i++) {
		if(parents[i] == -1) {
			root_of_each_tree.push_back(i);
		}
	}
	num_of_trees = root_of_each_tree.size();
	
	// dfs start from root to ensure 
	// discover time of child is bigger than discover time of parent
	for(int root : root_of_each_tree) {
		tree_nodes.clear();
		dfsVisit(root);
		forest.push_back(tree_nodes);
	}
}

void Graph::calculateTreeValues() {
	queue<int> q;
	for(int i = 0; i < vertices; i++) {
		long long tree_value = vertex_expenses[i];
		q.push(i);
		while(!q.empty()) {
			int curr = q.front();
			q.pop();
			
			for(int child : childs[curr]) {
				tree_value += vertex_expenses[child];
				q.push(child);
			}
		}
		tree_values[i] = tree_value;
	}
}

void Graph::dpEachTree() {
	
	dp.resize(num_of_trees);
	vector<vector<vector<bool>>> is_parent_take_tree(num_of_trees);
	
	for(int t = 0; t < num_of_trees; t++) {
		
		int curr_tree_size = forest[t].size();
		dp[t].resize(curr_tree_size + 1, vector<long long>(money + 1, 0));
		is_parent_take_tree[t].resize(curr_tree_size + 1, vector<bool>(money + 1, false));
		
		for(int i = 1; i <= curr_tree_size; i++) {
			
			int curr_node = forest[t][i - 1];
			int curr_parent = parents[curr_node];
			int curr_parent_idx = 0;
			if(curr_parent != -1) {
				int child_parent_relative_dist = dfs_discover_time[curr_node] - 
												 dfs_discover_time[curr_parent];
				curr_parent_idx = i - child_parent_relative_dist;
			}
			
			for(long long k = 1; k <= money; k++) {
				
				if(curr_parent != -1 && is_parent_take_tree[t][curr_parent_idx][k]) {
					dp[t][i][k] = dp[t][curr_parent_idx][k];
				    is_parent_take_tree[t][i][k] = true;
				    
				    long long curr_node_expense = vertex_expenses[curr_node];
					if(k >= curr_node_expense &&
					   !is_parent_take_tree[t][curr_parent_idx][k - curr_node_expense]) {
						if(curr_node_expense + dp[t][i - 1][k - curr_node_expense] > dp[t][i][k]) {
							dp[t][i][k] = curr_node_expense +
										  dp[t][i - 1][k - curr_node_expense];
							is_parent_take_tree[t][i][k] = false;
						}
					}
					
					long long curr_node_rooted_tree_expense = tree_expenses[curr_node];
					if(k >= curr_node_rooted_tree_expense &&
					   !is_parent_take_tree[t][curr_parent_idx][k - curr_node_rooted_tree_expense]) {
						if((tree_values[curr_node] + dp[t][i - 1][k - curr_node_rooted_tree_expense]) > 
							dp[t][i][k]) {
						       dp[t][i][k] = tree_values[curr_node] +
								   		     dp[t][i - 1][k - curr_node_rooted_tree_expense];
						}
					}
				    
						
				}
				else {
					dp[t][i][k] = dp[t][i - 1][k];
					
					long long curr_node_expense = vertex_expenses[curr_node];
					if(k >= curr_node_expense &&
					   !is_parent_take_tree[t][curr_parent_idx][k - curr_node_expense]) {
						
						dp[t][i][k] = max(dp[t][i][k], 
										  curr_node_expense +
										  dp[t][i - 1][k - curr_node_expense]
										 );
					}
					
					long long curr_node_rooted_tree_expense = tree_expenses[curr_node];
					if(k >= curr_node_rooted_tree_expense &&
					   !is_parent_take_tree[t][curr_parent_idx][k - curr_node_rooted_tree_expense]) {
						if((tree_values[curr_node] + dp[t][i - 1][k - curr_node_rooted_tree_expense]) > 
							dp[t][i][k]) {
						       dp[t][i][k] = tree_values[curr_node] +
								   		     dp[t][i - 1][k - curr_node_rooted_tree_expense];
							   is_parent_take_tree[t][i][k] = true;
						}
					}
				}
			}
		}
	}
}
	
void Graph::dpMergeAllTrees() {
	long long dp_merge[num_of_trees + 1][money + 1];
	memset(dp_merge, 0, sizeof(dp_merge));
	
	for(int t = 1; t <= num_of_trees; t++) {
		int curr_tree_size = forest[t - 1].size();
		
		for(int k = 1; k <= money; k++) {
			for(int m = 0; m <= k; m++) {
				dp_merge[t][k] = max(dp_merge[t][k], 
									 dp[t - 1][curr_tree_size][m] +
									 dp_merge[t - 1][k - m]
									);
			}
		}
	}
	
	cout << dp_merge[num_of_trees][money] << '\n';
}

void Graph::constructDP() {
	constructChilds();
	dfs();
	calculateTreeValues();
	dpEachTree();
	dpMergeAllTrees();
}


Graph::~Graph() {
	delete[] parents;
	delete[] childs;
	delete[] vertex_expenses;
	delete[] tree_expenses;
	delete[] tree_values;
	delete[] dfs_visited;
	delete[] dfs_discover_time;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int N, M;
	cin >> N >> M;
	Graph graph(N, M);
	
	for(int i = 0; i < graph.vertices; i++) {
		cin >> graph.parents[i];
	}
	for(int i = 0; i < graph.vertices; i++) {
		cin >> graph.vertex_expenses[i];
		cin >> graph.tree_expenses[i];
	}
	
	graph.constructDP();
	
	return 0;
}
