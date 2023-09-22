#pragma once

#include "Proc.h"

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

void printTable(const vector<Task>& tasks) {
	cout << "Waiting Time Table:\n";
	cout << "PId\tWT" << endl;
	unordered_map<int, int> WaitMap;
	float numTasks = 0.0f;
	float TotalWait = 0.0f;
	for (const Task t : tasks) {
		if (t.ct >= 0) {
			WaitMap[t.pid] = t.ct - t.bt - t.at;
			numTasks++;
			TotalWait += WaitMap[t.pid];
		}
	}
	for (const auto& p : WaitMap) {
		cout << p.first << "\t" << p.second << endl;
	}
	cout << "\nAvg. Waiting time: " << TotalWait/numTasks << "\n\nFinal Execution Sequence:\n";
}