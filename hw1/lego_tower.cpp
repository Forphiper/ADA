#include <iostream>
#include <vector>

using namespace std;

vector<string> operations;

void place(int x) {
	operations.push_back("PLACE " + to_string(x));
}

void pop() {
	operations.push_back("POP");
}

void photo() {
	operations.push_back("PHOTO");
}

void divideAndConquer(int left, int right) {
	if(left == right) {
		photo();
		return;
	}
	
	int mid = left + (right - left) / 2;
	// deal with the left part
	divideAndConquer(left, mid);
	// pop all elements in the stack
	// place the left part at bottome of stack
	// then place the righ part on top of stack
	for(int i = 0; i < right - left + 1; i++) {
		pop();
	}
	for(int i = left; i < mid + 1; i++) {
		place(i);
	}
	for(int i = right; i >= mid + 1; i--) {
		place(i);
	}
	// deal with the right part
	divideAndConquer(mid + 1, right);
}

int main()
{
	ios_base::sync_with_stdio (0);
	cin.tie (0);
	
	int n;
    cin >> n;
    
    for(int i = n; i >= 1; i--) {
		place(i);
    }
    
    divideAndConquer(1, n);
    
    cout << operations.size() << '\n';
    for(auto op : operations) {
		cout << op << '\n';
	}
    
    return 0;
}

