#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void printGanttChart(const vector<Task>& tasks, int spaces = 4) {
	int maxTime = 0;
	unordered_map<int, vector<pair<int, int>>> intervalMap;

	for (const Task& task : tasks) {
		maxTime = max(maxTime, task.intervals.second);
		intervalMap[task.pid].push_back(task.intervals);
	}

	cout << "Gantt Chart:" << endl;
	cout << " ";
	for (int i = 0; i <= maxTime; ++i) {
		cout << i;
		for (int j = 1; j < (i < 10 ? spaces : spaces - 1); ++j) {
			cout << ' ';
		}
	}
	cout << endl;

	for (const auto& kv : intervalMap) {
		int pid = kv.first;
		const vector<pair<int, int>>& intervals = kv.second;
		cout << "|";
		int i = 0;

		for (int currentTime = 0; currentTime <= maxTime; ++currentTime) {
			bool printed = false;

			for (const pair<int, int>& interval : intervals) {
				if (currentTime > interval.first && currentTime <= interval.second) {
					if (!printed) {
						for (; i < currentTime * spaces; ++i) {
							if (i % spaces == 0) {
								cout << '+';
								i++;
							}
							cout << '-';
							printed = true;
						}
					}
				}
			}

			if (!printed) {
				for (; i < currentTime * spaces; ++i) {
					if (i % spaces == 0) {
						cout << '+';
						i++;
					}
					cout << ' ';
				}
			}
		}

		cout << "| " << pid << endl;
	}
}
