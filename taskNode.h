#pragma once
#include "node.h"
#include <string>

class TaskNode : public Node {
public:
	TaskNode(std::string name);

	int day;
	int time;
};

