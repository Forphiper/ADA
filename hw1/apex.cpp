#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long combine(vector<int>& values, int left_table[100001], int right_table[100001], int left, int right, int mid) {
	// count number of values in the left
	for(int i = left; i <= mid; i++) {
		left_table[values[i]]++;
	}
	// count number of values in the right
	for(int i = mid + 1; i <= right; i++) {
		right_table[values[i]]++;
	}
	
	int min_value;
	vector<int> priorities(right - left + 1);
	
	// from mid to left, if smaller then update
	min_value = INT_MAX;
	for(int i = mid; i >= left; i--) {
		min_value = min(min_value, values[i]);
		priorities[i - left] = min_value;
	}
	// from mid + 1 to right, if smaller then update
	min_value = INT_MAX;
	for(int i = mid + 1; i <= right; i++) {
		min_value = min(min_value, values[i]);
		priorities[i - left] = min_value;
	}
	
	long long cross_middle_num = 0;
	int i = left;
	int j = right;
	// start from left and right
	while(i <= mid && j >= mid + 1) {
		if(priorities[i - left] <= priorities[j - left]) {
			// check the lower boundary
			if(values[i] - priorities[i - left] >= priorities[i - left]) {
				cross_middle_num += right_table[values[i] - priorities[i - left]];
			}
			// check the upper boundary
			if(priorities[i - left] != 0) {
				if(values[i] + priorities[i - left] <= 100000) {
					cross_middle_num += right_table[values[i] + priorities[i - left]];
				}
			}
			
			left_table[values[i++]]--;
		}
		else {
			if(values[j] - priorities[j - left] >= priorities[j - left]) {
				cross_middle_num += left_table[values[j] - priorities[j - left]];
			}
			if(priorities[j - left] != 0) {
				if(values[j] + priorities[j - left] <= 100000) {
					cross_middle_num += left_table[values[j] + priorities[j - left]];
				}
			}
			
			right_table[values[j--]]--;
		}
	}
	
	// clear the tables to 0
	while(i <= mid) {
		left_table[values[i++]]--;
	}
	while(j >= mid + 1) {
		right_table[values[j--]]--;
	}
	
	return cross_middle_num;
}

long long numberOfPairs(vector<int>& values, int left_table[100001], int right_table[100001], int left, int right) {
	if(left >= right)
		return 0;
		
	int mid = left + (right - left) / 2;
	
	long long left_num = numberOfPairs(values, left_table, right_table, left, mid);
	long long right_num = numberOfPairs(values, left_table, right_table, mid + 1, right);
	long long cross_middle_num = combine(values, left_table, right_table, left, right, mid);
	
	return (left_num + right_num + cross_middle_num);
}

int main()
{
	int n;
	cin >> n;

	int ai;
	vector<int> values(n);
	for(int i = 0; i < n; i++) {
		cin >> ai;
		values[i] = ai;
	}
	
	// value range from 1 to 100000
	int left_table[100001] = {0};
	int right_table[100001] = {0};
	
	long long count = 0;
	count = numberOfPairs(values, left_table, right_table, 0, n - 1);
	
	cout << count << '\n';
    
    return 0;
}

