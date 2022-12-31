#include <iostream>

using namespace std;

int main()
{
	int i, n;
    int num;
    
    cin >> n;
    cin >> num;
    
    long long int sum = num;
    long long int max_value = num;
    
    for(i = 1; i < n; i++) {
		cin >> num;
        if(sum < 0) {
            sum = num;
        }
        else {
            sum += num;
        }
        max_value = max(max_value, sum);
    }
    
    cout << max_value << "\n";

    return 0;
}
