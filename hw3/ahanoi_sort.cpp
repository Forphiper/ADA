#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;


bool compareByWeight(const pair<long long, int>&a, const pair<long long, int>&b) {
	return a.first < b.first;
}

bool compareByIndex(const pair<long long, int>&a, const pair<long long, int>&b) {
	return a.second > b.second;
}

class Rod {
public:
	stack<long long> rod;
	vector<long long> prefix_sum;
	int num_of_largest;
	long long sum_of_weights;
	int curr_rod_size;
	vector<pair<long long, int>> tmp_vec;
	
	void take();
	void put(long long weight);
	void cc(int num_of_takeoff, int divisor);
	void dd(int num_of_takeoff);
	
};


void Rod::put(long long weight) {
	
	rod.push(weight);
	if(prefix_sum.empty()) {
		prefix_sum.push_back(weight);
	} 
	else {
		prefix_sum.push_back(prefix_sum.back() + weight);
	}
}

void Rod::take() {
	cout << rod.top() << '\n';
	rod.pop();
	prefix_sum.pop_back();
}

void Rod::cc(int num_of_takeoff, int divisor) {
	
	num_of_largest = ceil((double)num_of_takeoff / (double)divisor);
	sum_of_weights = 0;
	curr_rod_size = rod.size();
	
	tmp_vec.clear();
	for(int j = 0; j < num_of_takeoff; j++) {
		tmp_vec.push_back(make_pair(rod.top(), j));
		rod.pop();
		prefix_sum.pop_back();
	}

	sort(tmp_vec.begin(), tmp_vec.end(), compareByWeight);
	for(int j = 0; j < num_of_largest; j++) {
		sum_of_weights += tmp_vec[tmp_vec.size() - num_of_largest + j].first;
	}

	sort(tmp_vec.begin(), tmp_vec.end() - num_of_largest, compareByIndex);
	for(int j = 0; j < (int)tmp_vec.size() - num_of_largest; j++) {
		rod.push(tmp_vec[j].first);
		if(prefix_sum.empty()) {
			prefix_sum.push_back(tmp_vec[j].first);
		}
		else {
			prefix_sum.push_back(prefix_sum.back() + tmp_vec[j].first);
		}
	}
	cout << sum_of_weights << '\n';
}

void Rod::dd(int num_of_takeoff) {
	
	curr_rod_size = rod.size();
	
	if(num_of_takeoff == curr_rod_size) {
		cout << prefix_sum.back() << '\n';
	}
	else {
		cout << prefix_sum[curr_rod_size - 1] - prefix_sum[curr_rod_size - num_of_takeoff - 1] << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	Rod r;
	
	long long weight;
	int num_of_takeoff;
	int divisor;
	int rounds;
	string event;
	cin >> rounds;
	for(int i = 0; i < rounds; i++) {
		cin >> event;
		if(event == "PUT") {
			cin >> weight;
			r.put(weight);
		}
		else if(event == "TAKE") {
			r.take();
		}
		else if(event == "CC") {
			cin >> num_of_takeoff;
			cin >> divisor;
			r.cc(num_of_takeoff, divisor);
		}
		else if(event == "DD") {
			cin >> num_of_takeoff;
			r.dd(num_of_takeoff);
		}
	}
	
	return 0;
}
