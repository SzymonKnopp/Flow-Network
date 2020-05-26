#pragma once
#include <string>
#include "task.h"

class Group {
public:
	Group();
	~Group();

	std::string name;
	int groupHours;
	int taskCount;
	task* tasks;

private:
	task newTask();
};

