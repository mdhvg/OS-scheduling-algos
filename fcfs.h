#include "Proc.h"

#include <queue>
#include <vector>

using namespace std;

struct FirstCome
{
	{
		return p1.at > p2.at;
	}
};

vector<Task> fcfs(vector<process>& processes)
{
	priority_queue<process, vector<process>, FirstCome> pq;
	vector<Task> runs;
	int numProcesses = processes.size();
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
		int wt = tat - top.bt;
		runs.push_back({ top.pid, {currentTime, currentTime + top.bt}, currentTime + top.bt, top.at, top.bt });
		currentTime += top.bt;
		pq.pop();
	}
	return runs;
}