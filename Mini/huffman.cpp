#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct HeapNode {
	int data;
	unsigned long long frequency;
	HeapNode *left;
	HeapNode *right;
	
	HeapNode(unsigned long long f, int d) {
		data = d;
		frequency = f;
		left = NULL;
		right = NULL;
	}
};

struct compareTwoNodes {
	bool operator()(HeapNode *a, HeapNode *b) {
		return a->frequency > b->frequency;
		/*
		if(a->frequency > b->frequency) return true;
		if(a->frequency < b->frequency) return false;
		
		return a->data < b->data;
		*/
	}
};

void encodingData(struct HeapNode *root, string curr_str, vector<pair<int, string>>& results) {
	if(!root) {
		return;
	}
	if(root->data != 0) {
		results.push_back(make_pair(root->data, curr_str));
	}
	
	encodingData(root->left, curr_str + "0", results);
	encodingData(root->right, curr_str + "1", results);
}

bool compareTwoData(const pair<int, string>& a, const pair<int, string>& b) {
	return a.first < b.first;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	if(n == 1) {
		cout << "0" << '\n';
		return 0;
	}
	unsigned long long frequencies[n];
	for(int i = 0; i < n; i++) {
		cin >> frequencies[i];
	}
	
	priority_queue<HeapNode*, vector<HeapNode*>, compareTwoNodes> min_heap;
	
	for(int i = 0; i < n; i++) {
		min_heap.push(new HeapNode(frequencies[i], i + 1));
	}
	
	struct HeapNode *left, *right, *parent;
	while(min_heap.size() != 1) { // total (n - 1) pass
		left = min_heap.top();
		min_heap.pop();
		
		right = min_heap.top();
		min_heap.pop();

		parent = new HeapNode(left->frequency + right->frequency, 0);
		parent->left = left;
		parent->right = right;
		
		min_heap.push(parent);
	}
	
	vector<pair<int, string>> results;
	encodingData(min_heap.top(), "", results);
	sort(results.begin(), results.end(), compareTwoData);
	for(auto res : results) {
		cout << res.second << '\n';
	}
	
	
	
	return 0;
}
