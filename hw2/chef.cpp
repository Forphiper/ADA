#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool sortByPairsSecond(const pair<int, int>&a, const pair<int, int>&b) {
	return (a.second > b.second);
}

long long getGroupLeaveTime(vector<pair<int, int>>& group_data, int group_size) {
	sort(group_data.begin(), group_data.end(), sortByPairsSecond);
	long long leave_time = group_data[0].first + group_data[0].second;
	long long current_cook_time = group_data[0].first;
	
	for(int i = 1; i < group_size; i++) {
		leave_time = max(leave_time, current_cook_time + group_data[i].first + group_data[i].second);
		current_cook_time += group_data[i].first;
	}
	
	return leave_time;
}

long long getGroupCookTime(vector<pair<int, int>>& group_data, int group_size) {
	long long cook_time = 0;
	for(int i = 0; i < group_size; i++) {
		cook_time += group_data[i].first;
	}
	return cook_time;
}

bool sortGroups(const vector<long long>& a, const vector<long long>& b) {
	return ((a[1] * a[2] + (a[0] + b[1]) * b[2]) < (b[1] * b[2] + (b[0] + a[1]) * a[2]));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	int mi;
	int aj, bj;
	vector<vector<pair<int, int>>> raw_datas(n);
	int group_size[n];
	vector<pair<int, int>> tmp_vec;
	for(int i = 0; i < n; i++) {
		cin >> mi;
		group_size[i] = mi;
		tmp_vec.resize(mi);
		for(int j = 0; j < mi; j++) {
			cin >> aj;
			cin >> bj;
			tmp_vec[j].first = aj;
			tmp_vec[j].second = bj;
		}
		raw_datas[i] = tmp_vec;
	}
	
	vector<vector<long long>> group_as_one(n);
	for(int i = 0; i < n; i++) {
		group_as_one[i].push_back(getGroupCookTime(raw_datas[i], group_size[i]));
		group_as_one[i].push_back(getGroupLeaveTime(raw_datas[i], group_size[i]));
		group_as_one[i].push_back(group_size[i]);
	}
	
	sort(group_as_one.begin(), group_as_one.end(), sortGroups);
	
	long long min_sum = 0;
	long long current_cook_time = 0;
	min_sum += group_as_one[0][1] * group_as_one[0][2];
	current_cook_time = group_as_one[0][0];
	for(int i = 1; i < n; i++) {
		min_sum += ((current_cook_time + group_as_one[i][1]) * group_as_one[i][2]);
		current_cook_time += group_as_one[i][0];
	}
	
	cout << min_sum << '\n';
	
	
	return 0;
}
