#pragma once

#include "Proc.h"

#include <queue>
#include <unordered_map>

struct Priority
{
	bool operator()(process& p1, process& p2)
	{
		return p1.priori > p2.priori;
	}
};

struct PriorityArrival
{
	bool operator()(process& p1, process& p2)
	{
		if (p1.at == p2.at) {
			return (p1.at) * (p1.priori) > (p2.at) * (p2.priori);
		}
		return p1.at > p2.at;

	}
};

vector<Task> priori_p(vector<process>& processes) {
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
		if (!pq_pri.empty() && pq_pri.top().priori < top.priori) {
			tasks.push_back({ top.pid, {currentTime, pq_pri.top().at}, 0 });
			pq_pri.push({ top.pid, top.at, top.bt - (pq_pri.top().at - currentTime), top.priori });
		}
		else {
			tasks.push_back({ top.pid, {currentTime, currentTime + top.bt}, currentTime + top.bt, top.at, procBt[top.pid]});
			currentTime += top.bt;
		}
	}
	return tasks;
}
