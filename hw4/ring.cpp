#include <iostream>

using namespace std;

const int MAXN = 400;
int n;
long long values[MAXN + 1][MAXN + 1];
int rings[MAXN][MAXN];
long long max_values[MAXN];
long long dp[MAXN][MAXN + 1][MAXN + 1];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> values[i][j];
		}
	}
	
	// create n rings
	for(int i = 0; i < n; i++) {
		rings[0][i] = i + 1;
	}
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < n; j++) {
			rings[i][j] = rings[i - 1][j] + 1;
			if(rings[i][j] > n) {
				rings[i][j] -= n;
			}
		}
	}
	
	// dp computation
	for(int r = 0; r < n; r++) {
		
		for(int i = 0; i <= n - r - 1; i++) {
			for(int j = 1; j <= i; j++) {
				if(j == 1) {
					int start = rings[r][0];
					int end = rings[r][i - 1] + 1;
					if(end > n) end -= n;
					dp[r][i][j] = values[start][end];
				}
				else {
					for(int m = j - 1; m <= i - 1; m++) {
						int start = rings[r][m];
						int end = rings[r][i - 1] + 1;
						if(end > n) end -= n;
						dp[r][i][j] = max(dp[r][i][j], dp[r][m][j - 1] + values[start][end]);
					}
				}
			}
		}
		
		// i == n - r
		for(int j = 1; j <= n - r; j++) {
			if(j == 1) {
				int start = rings[r][0];
				int end = rings[r][n - 1] + 1;
				if(end > n) end -= n;
				dp[r][n - r][j] = values[start][end];
			}
			else {
				for(int m = j - 1; m <= n - r - 1; m++) {
					int start = rings[r][m];
					int end = rings[r][n - 1] + 1;
					if(end > n) end -= n;
					dp[r][n - r][j] = max(dp[r][n - r][j], dp[r][m][j - 1] + values[start][end]);
				}
			}
		}
		
		
		for(int i = 0; i < n; i++) {
			max_values[i] = max(max_values[i], dp[r][n - r][i + 1]);
		}
	}
	
	for(int i = 0; i < n; i++) {
		cout << max_values[i] << ' ';
	}
	cout << '\n';
	
	
	return 0;
}
