#pragma once
#include "proc.h"

#include <queue>
#include <unordered_map>

vector<Task> priori_np(vector<process>& processes) {
	priority_queue<process, vector<process>, PriorityArrival> pq_at;
	priority_queue<process, vector<process>, Priority> pq_pri;
	unordered_map<int, int> procBt;
	for (process p : processes) {
		pq_at.push(p);
		procBt[p.pid] = p.bt;
	}

	int n = processes.size();
	vector<Task> tasks;
	int currentTime = 0;
	process top;

	while (!pq_at.empty() || !pq_pri.empty()) {
		if (pq_pri.empty()) {
			top = pq_at.top();
			pq_at.pop();
		}
		else {
			top = pq_pri.top();
			pq_pri.pop();
		}
		currentTime = max(currentTime, top.at);
		while (!pq_at.empty() && pq_at.top().priori <= top.priori && pq_at.top().at <= currentTime + top.bt) {
			pq_pri.push(pq_at.top());
			pq_at.pop();
		}
		tasks.push_back({ top.pid, {currentTime, currentTime + top.bt}, currentTime + top.bt, top.at, top.bt});
		currentTime += top.bt;
	}
	return tasks;
}