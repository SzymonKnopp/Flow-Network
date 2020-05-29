#pragma once
#include "pipe.h"
#include <string>
#include <vector>

class Node {
public:
	Node(std::string name);
	~Node();

	void addOutPipe(Node* sink, int capacity);
	virtual bool isSink() const;

	std::string name;
	bool active;
	bool usedInPath;
	std::vector<pipe*> pipesIn;
	std::vector<pipe*> pipesOut;
};

