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
	//for Ford-Fulkerson algorithm, return node viable for traversal
	Node* goThrough(std::stack<pipe*>& path) const;


private:
	const int _step;
	std::vector<pipe*> _pipesIn;
	std::vector<pipe*> _pipesOut;
};

