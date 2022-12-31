#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

// max heap, compare by second element
struct pqCompareByIndex {
	bool operator()(const pair<long long, long long>& a, 
					const pair<long long, long long>& b) {
        return a.second < b.second;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int rounds;
	string event;
	stack<long long> rod;
	
	long long weight;
	vector<long long> prefix_sum;
	int num_of_takeoff;
	int divisor;
	int num_of_largest;
	long long sum_of_weights;
	int original_order;
	int curr_rod_size;
	priority_queue< pair<long long, long long>, 
					vector<pair<long long, long long>>, 
					greater<pair<long long, long long>> > pq_largest;
	priority_queue< pair<long long, long long>, 
					vector<pair<long long, long long>>, 
					pqCompareByIndex > pq_remaining;
	
	cin >> rounds;
	for(int i = 0; i < rounds; i++) {
		cin >> event;
		if(event == "PUT") {
			cin >> weight;
			rod.push(weight);
			if(prefix_sum.empty()) {
				prefix_sum.push_back(weight);
			} 
			else {
				prefix_sum.push_back(prefix_sum.back() + weight);
			}
		}
		else if(event == "TAKE") {
			cout << rod.top() << '\n';
			rod.pop();
			prefix_sum.pop_back();
		}
		else if(event == "CC") {
			cin >> num_of_takeoff;
			cin >> divisor;
			num_of_largest = ceil((double)num_of_takeoff / (double)divisor);
			sum_of_weights = 0;
			curr_rod_size = rod.size();
			original_order = 0;
			
			// put ceil(x/k) largest to eat in pq_largest
			for(int j = 0; j < num_of_takeoff; j++) {
				pq_largest.push(make_pair(rod.top(), original_order));
				original_order++;
				rod.pop();
				prefix_sum.pop_back();
				
				if((int)pq_largest.size() > num_of_largest) {
					pq_remaining.push(pq_largest.top());
					pq_largest.pop();
				}
			}
			while(!pq_largest.empty()) {
				sum_of_weights += pq_largest.top().first;
				pq_largest.pop();
			}
			cout << sum_of_weights << '\n';
			
			// put remaining elements back to rod and calculate prefix
			while(!pq_remaining.empty()) {
				rod.push(pq_remaining.top().first);
				if(prefix_sum.empty()) {
					prefix_sum.push_back(pq_remaining.top().first);
				}
				else {
					prefix_sum.push_back(prefix_sum.back() + pq_remaining.top().first);
				}
				pq_remaining.pop();
			}
			
		}
		else if(event == "DD") {
			cin >> num_of_takeoff;
			curr_rod_size = rod.size();
			
			if(num_of_takeoff == curr_rod_size) {
				cout << prefix_sum.back() << '\n';
			}
			else {
				cout << prefix_sum[curr_rod_size - 1] - prefix_sum[curr_rod_size - num_of_takeoff - 1] << '\n';
			}
		}
	}
	
	return 0;
}
