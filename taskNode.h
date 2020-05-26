#pragma once
#include "node.h"
#include <string>

class TaskNode : public Node {
public:
	TaskNode(std::string name, int step);

	int day;
	int time;
};

