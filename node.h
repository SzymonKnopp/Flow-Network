#pragma once
#include "pipe.h"
#include <string>
#include <vector>

class Node {
public:
	Node(std::string name, int step);
	~Node();

	void addOutPipe(Node* sink, int capacity);
	virtual bool isSink() const;

	std::string name;
	std::vector<pipe*> pipesIn;
	std::vector<pipe*> pipesOut;

	//necessary?
	const int step;
};

