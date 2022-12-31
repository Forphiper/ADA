
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int n, w;
	cin >> n >> w;
	
	vector<int> values(n);
	for(int i = 0; i < n; i++) {
		cin >> values[i];
	}
	
	vector<int> greedy(w);
	vector<int> dp(w + 1, 0);
	
	sort(values.begin(), values.end());
	
	// solution using greedy
	for(int i = 0; i < w; i++) {
		greedy[i] = i + 1;
		for(int j = n - 1; j >= 0; j--) {
			if(values[j] > w) {
				continue;
			}
			else {
				greedy[i] = greedy[i] % values[j];
			}
		}
	}
	
	// optimal solution using dp
	for(int i = 0; i < w + 1; i++) {
		for(int j = 0; j < n; j++) {
			if(i >= values[j]) {
				dp[i] = max(dp[i], dp[i - values[j]] + values[j]);
			}
		}
	}
	
	for(int i = 0; i < w; i++) {
		dp[i + 1] = (i + 1) - dp[i + 1]; // cash - spend
		cout << greedy[i] - dp[i + 1]  << '\n';
	}

    return 0;
}

