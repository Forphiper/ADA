#include <iostream>
#include <climits>

using namespace std;

const long long MAXN = 1000;
const long long MAXK = 500;
int n, k;
long long values[MAXN];
long long maximum_sums[MAXN][MAXN];
long long dp[MAXK + 1][MAXN + 1];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		cin >> values[i];
	}
	
	// all pairs of maximum sum
    for(int i = 0; i < n; i++) {
		long long curr_sum = values[i];
		long long curr_max_value = values[i];
		maximum_sums[i][i] = curr_max_value;
		for(int j = i + 1; j < n; j++) {
			if(curr_sum < 0) {
				curr_sum = values[j];
			}
			else {
				curr_sum += values[j];
			}
			curr_max_value = max(curr_max_value, curr_sum);
			maximum_sums[i][j] = curr_max_value;
		}
	}
	
	// dp computation
	for(int i = 1; i < n + 1; i++) {
		dp[1][i] = maximum_sums[0][i - 1] * i;
	}
	
	for(int i = 2; i < k + 1; i++) {
		for(int j = i; j < n + 1; j++) {
			dp[i][j] = LLONG_MAX;
			for(int m = i - 1; m < j; m++) {
				dp[i][j] = min(dp[i][j], dp[i - 1][m] + maximum_sums[m][j - 1] * (j- m));
			}
		}
	}
	
	cout << dp[k][n] << '\n';
	
	return 0;
}
