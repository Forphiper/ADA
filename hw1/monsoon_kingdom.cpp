#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long mergeBelowL(vector<double>& vect, int left, int right, int mid) {
	vector<double> output_vect(right - left + 1);
	int i = left;
	int j = mid + 1;
	int k = 0;
	long long inversion_count = 0;
	
	while((i <= mid) && (j <= right)) {
		if(vect[i] <= vect[j]) {
			output_vect[k++] = vect[i++];
		}
		else {
			output_vect[k++] = vect[j++];
			inversion_count += (mid - i + 1);
		}
	}
	
	while(i <= mid) {
		output_vect[k++] = vect[i++];
	}
	
	while(j <= right) {
		output_vect[k++] = vect[j++];
	}
	
	for(int p = left; p <= right; p++) {
		vect[p] = output_vect[p - left];
	}
	
	return inversion_count;
}

long long numberOfInversionBelowL(vector<double>& vect, int i, int j) {
	if(i >= j)
		return 0;
		
	int mid = i + (j - i) / 2;
	long long left_num = numberOfInversionBelowL(vect, i, mid);
	long long right_num = numberOfInversionBelowL(vect, mid + 1, j);
	
	long long cross_middle_num = mergeBelowL(vect, i, j, mid);
	return (left_num + right_num + cross_middle_num);
}

long long mergeBelowR(vector<double>& vect, int left, int right, int mid) {
	vector<double> output_vect(right - left + 1);
	int i = left;
	int j = mid + 1;
	int k = 0;
	long long inversion_count = 0;
	
	while((i <= mid) && (j <= right)) {
		if(vect[j] <= vect[i]) {
			output_vect[k++] = vect[j++];
			inversion_count += (mid - i + 1);
		}
		else {
			output_vect[k++] = vect[i++];
		}
	}
	
	while(i <= mid) {
		output_vect[k++] = vect[i++];
	}
	
	while(j <= right) {
		output_vect[k++] = vect[j++];
	}
	
	for(int p = left; p <= right; p++) {
		vect[p] = output_vect[p - left];
	}
	
	return inversion_count;
}

long long numberOfInversionBelowR(vector<double>& vect, int i, int j) {
	if(i >= j)
		return 0;
		
	int mid = i + (j - i) / 2;
	long long left_num = numberOfInversionBelowR(vect, i, mid);
	long long right_num = numberOfInversionBelowR(vect, mid + 1, j);
	
	long long cross_middle_num = mergeBelowR(vect, i, j, mid);
	return (left_num + right_num + cross_middle_num);
}

int main()
{
	int n;
	long long l1, l2, r1, r2;
	
	cin >> n;
	cin >> l1 >> l2 >> r1 >> r2;
	
	long long xi, yi;
	vector<pair<long long, long long>> coordinates(n);
	
	for(int i = 0; i < n; i++) {
		cin >> xi >> yi;
		coordinates[i].first = xi;
		coordinates[i].second = yi;
	}
	
	sort(coordinates.begin(), coordinates.end());
	
	vector<double> below_r_vect(n);
	vector<double> below_l_vect(n);
	
	for(int i = 0; i < n; i++) {
		below_r_vect[i] = (1.0 * coordinates[i].second * r2 - coordinates[i].first * r1) / r2;
		below_l_vect[i] = (1.0 * coordinates[i].second * l2 - coordinates[i].first * l1) / l2;
	}
	
	long long below_r_inversion_number = numberOfInversionBelowR(below_r_vect, 0, n - 1);
	long long below_l_inversion_number = numberOfInversionBelowL(below_l_vect, 0, n - 1);
	long long ans = below_r_inversion_number - below_l_inversion_number;
	
	cout << ans << '\n';
	

    return 0;
}

