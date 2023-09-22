#include "fcfs.h"
#include "sjfs.h"
#include "srtf.h"
#include "rr.h"
#include "priori_p.h"
#include "priori_np.h"
#include "Chart.h"
#include "Table.h"

#include <iostream>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	int n;
	cout << "Enter number of processes: ";
	cin >> n;
	vector<process> processes(n);
	cout << "Enter arrival time, burst time and priority of each process: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "Process " << i + 1 << ": ";
		cin >> processes[i].at >> processes[i].bt >> processes[i].priori;
		processes[i].pid = i + 1;
	}

	//vector<process> processes = {
	//	//  pid		at		bt		priori
	//		{1,		3,		2,		1}, // 1
	//		{2,		6,		2,		2}, // 2
	//		{3,		4,		4,		3}, // 3
	//		{4,		3,		6,		4}, // 4
	//		{5,		2,		8,		5}, // 5
	//};

	int choice;
	cout << "Choose algorithm: " << endl;
	cout << "1. FCFS" << endl;
	cout << "2. SJFS" << endl;
	cout << "3. SRTF" << endl;
	cout << "4. Round Robin" << endl;
	cout << "5. Priority (Preemptive)" << endl;
	cout << "6. Priority (Non-Preemptive)" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	vector<Task> tasks;

	switch (choice) {
	case 1:
		// FCFS
	{
		cout << "FCFS" << endl;
		tasks = fcfs(processes);
		break;
	}
	case 2:
		// SJFS
	{
		cout << "SJFS" << endl;
		tasks = sjfs(processes);
		break;
	}
	case 3:
		// SRTF
	{
		cout << "SRTF" << endl;
		tasks = srtf(processes);
		break;
	}
	case 4:
		// RR
	{
		cout << "Round Robin" << endl;
		int quantum;
		cout << "Enter quantum: ";
		cin >> quantum;
		tasks = rr(processes, quantum);
		break;
	}
	case 5:
		// Priority (Preemptive)
	{
		cout << "Priority (Preemptive)" << endl;
		tasks = priori_p(processes);
		break;
	}
	case 6:
		// Priority (Non-Preemptive)
	{
		cout << "Priority (Non-Preemptive)" << endl;
		tasks = priori_np(processes);
		break;
	}
	default:
		cout << "Invalid choice!" << endl;
	}
	printTable(tasks);
	printGanttChart(tasks);

	return 0;
}
