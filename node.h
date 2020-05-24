#pragma once
#include "pipe.h"
#include <vector>
#include <stack>

class Node {
public:
	Node(int step);
	~Node();

	void addOutPipe(Node* sink, int capacity);
	virtual bool isSink() const;

	std::vector<pipe*> pipesIn;
	std::vector<pipe*> pipesOut;

	//necessary?
	const int step;
};

