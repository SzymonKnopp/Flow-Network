#include "taskGroup.h"
#include <iostream>

using namespace std;

TaskGroup::TaskGroup() {
	cin >> name;
	cin >> taskCount;
	cin >> groupHours;
	tasks = new task[taskCount];
	for (int i = 0; i < taskCount; i++) {
		tasks[i] = newTask();
	}
}
TaskGroup::~TaskGroup() {
	delete[] tasks;
}

task TaskGroup::newTask() {
	task newTask;
	cin >> newTask.day;
	cin >> newTask.time;
	cin >> newTask.minHours;
	cin >> newTask.maxHours;
	return newTask;
}
