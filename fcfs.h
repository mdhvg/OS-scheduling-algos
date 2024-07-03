#include "Proc.h"

#include <queue>
#include <vector>

using namespace std;

struct FirstCome
{
	bool operator()(const process& p1, const process& p2)
	{
		return p1.at > p2.at;
	}
};

vector<Task> fcfs(vector<process>& processes)
{
	priority_queue<process, vector<process>, FirstCome> pq;
	vector<Task> runs;
	for (process proc : processes)
	{
		pq.push(proc);
	}

	int currentTime = 0;
	while (!pq.empty())
	{
		process top = pq.top();
		if (currentTime < top.at) {
			currentTime = top.at;
		}
		int ct = currentTime + top.bt;
		int tat = ct - top.at;
		runs.push_back({ top.pid, {currentTime, currentTime + top.bt}, currentTime + top.bt, top.at, top.bt });
		currentTime += top.bt;
		pq.pop();
	}
	return runs;
}
