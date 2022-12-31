#include "choose.h"
#include <algorithm>

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/

bool sortDescending(const int a, const int b) {
	if(compare_task(a, b) == 1) return true;
	return false;
}

void schedule(int N) {
	int tasks[N];
	for(int i = 0; i < N; i++) {
		tasks[i] = i + 1;
	}
	
	// sort tasks by its duration in descending order
	std::sort(tasks, tasks + N, sortDescending);
	
	int curr_machine1_finish_time = 0;
	int curr_machine2_finish_time = 0;
	for(int i = 0; i < N; i++) {
		// assign task to machine which has an earlier finish time
		if(curr_machine1_finish_time <= curr_machine2_finish_time) {
			curr_machine1_finish_time = assign_task(1, tasks[i]);
		}
		else {
			curr_machine2_finish_time = assign_task(2, tasks[i]);
		}
	}
}

