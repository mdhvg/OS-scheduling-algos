#include "proc.h"

#include <queue>
#include <unordered_map>

vector<Task> rr(vector<process>& processes, int tq = 2) {
	priority_queue<process, vector<process>, ArrivalTime> pq_at;
	queue<process> ready;
	unordered_map<int, int> procBt;
	for (process p : processes) {
		pq_at.push(p);
		procBt[p.pid] = p.bt;
	}

	int n = processes.size();
	vector<Task> tasks;
	int currentTime = 0;
	process top;

	while (!pq_at.empty() || !ready.empty()) {
		if (ready.empty()) {
			top = pq_at.top();
			pq_at.pop();
		}
		else {
			top = ready.front();
			ready.pop();
		}
		currentTime = max(currentTime, top.at);
		if (top.bt - tq > 0) {
			tasks.push_back({ top.pid, {currentTime, currentTime + tq}, 0 });
			currentTime += tq;
			while (!pq_at.empty() && pq_at.top().at <= currentTime) {
				ready.push(pq_at.top());
				pq_at.pop();
			}
			ready.push({ top.pid, top.at, top.bt - tq });
		}
		else {
			cout << top.pid << ": " << currentTime + top.bt << endl;
			tasks.push_back({ top.pid, {currentTime, currentTime + top.bt}, currentTime + top.bt, top.at, procBt[top.pid]});
			currentTime += top.bt;
			while (!pq_at.empty() && pq_at.top().at <= currentTime) {
				ready.push(pq_at.top());
				pq_at.pop();
			}
		}
	}
	return tasks;
}
