#pragma once
#include <string>
#include "task.h"

class TaskGroup {
public:
	TaskGroup();
	~TaskGroup();

	std::string name;
	int groupHours;
	int taskCount;
	task* tasks;

private:
	task newTask();
};

