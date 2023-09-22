#include "Proc.h"

#include <queue>
#include <iostream>
#include <vector>

using namespace std;

struct ArrivalTime
{
	bool operator()(process& p1, process& p2)
	{
		return p1.at > p2.at;
	}
};

struct ShortestJob
{
	bool operator()(process& p1, process& p2)
	{
		return p1.bt > p2.bt;
	}
};

vector<Task> sjfs(vector<process>& processes)
{
	priority_queue<process, vector<process>, ArrivalTime> pq_at;
	priority_queue<process, vector<process>, ShortestJob> ready;
	vector<Task> runs;
	for (process proc : processes)
	{
		pq_at.push(proc);
	}

	int currentTime = 0;
	process top;

	while (!pq_at.empty() || !ready.empty()) {
		if (ready.empty()) {
			top = pq_at.top();
			pq_at.pop();
		}
		else {
			top = ready.top();
			ready.pop();
		}
		if (currentTime < top.at) {
			currentTime += top.at;
		}
		Task t = { top.pid, make_pair(currentTime, currentTime + top.bt), currentTime + top.bt, top.at, top.bt};
		currentTime += top.bt;
		runs.push_back(t);
		while (!pq_at.empty() && pq_at.top().at <= currentTime) {
			ready.push(pq_at.top());
			pq_at.pop();
		}
	}

	return runs;
}