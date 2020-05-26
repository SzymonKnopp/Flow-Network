#include "group.h"
#include <iostream>

using namespace std;

Group::Group() {
	cin >> name;
	cin >> taskCount;
	cin >> groupHours;
	tasks = new task[taskCount];
	for (int i = 0; i < taskCount; i++) {
		tasks[i] = newTask();
		groupHours -= tasks[i].minHours;
	}
}
Group::~Group() {
	delete[] tasks;
}

task Group::newTask() {
	task newTask;
	cin >> newTask.day;
	cin >> newTask.time;
	cin >> newTask.minHours;
	cin >> newTask.maxHours;
	return newTask;
}
