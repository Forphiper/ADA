#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	string X;
	string Y;
	
	cin >> X;
	cin >> Y;
	
	int n1 = X.length();
	int n2 = Y.length();
	
	int dp[n1 + 1][n2 + 1] = {0};
	
	for(int i = 0; i < n1 + 1; i++) {
		dp[i][0] = i;
	}
	for(int i = 0; i < n2 + 1; i++) {
		dp[0][i] = i;
	}
	
	for(int i = 1; i < n1 + 1; i++) {
		for(int j = 1; j < n2 + 1; j++) {
			if(X[i - 1] == Y[j - 1]) {
				dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1] - 1));
			}
			else {
				dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
			}
		}
	}
	
	cout << dp[n1][n2] << '\n';	
	
	return 0;
}
