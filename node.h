#pragma once
#include "pipe.h"
#include <vector>

class Node {
public:
	Node(int step);

	void addOutPipe(Node* sink, int capacity);

	//for Ford-Fulkerson algorithm, return node viable for traversal
	Node* goThrough() const;

private:
	const int _step;
	std::vector<pipe*> _pipesIn;
	std::vector<pipe*> _pipesOut;
};

