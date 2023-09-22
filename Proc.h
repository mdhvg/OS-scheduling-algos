#pragma once

#include <vector>

using namespace std;

struct process {
	int pid;
	int at;
	int bt;
	int priori; // smaller ⬆️
};

struct Task
{
	int pid;
	pair<int, int> intervals;
	int ct = -1;
	int at;
	int bt;
};