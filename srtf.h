#include "Proc.h"

#include <queue>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<Task> srtf(vector<process>& processes) {
	priority_queue<process, vector<process>, ArrivalTime> pq_at;
	priority_queue<process, vector<process>, ShortestJob> ready;
	unordered_map<int, pair<int, int>> ProcMap;
	vector<Task> runs;
	int numProcesses = processes.size();

	for (process proc : processes) {
		pq_at.push(proc);
		ProcMap[proc.pid] = { proc.at, proc.bt };
	}

	int currentTime = 0;

	while (!pq_at.empty() || !ready.empty()) {
		while (!pq_at.empty() && pq_at.top().at <= currentTime) {
			ready.push(pq_at.top());
			pq_at.pop();
		}
		if (!ready.empty()) {
			process top = ready.top();
			ready.pop();
			currentTime++;
			top.bt--;
			if (runs.empty() || runs.back().pid != top.pid) {
				Task t = { top.pid, {currentTime - 1, currentTime}, currentTime + 1, top.at, ProcMap[top.pid].second};
				runs.push_back(t);
			}
			else {
				runs.back().intervals.second = currentTime;
			}
			if (top.bt > 0) {
				ready.push(top);
			}
		}
		else {
			currentTime++;
		}
	}
	return runs;
}