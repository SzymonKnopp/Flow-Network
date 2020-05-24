#pragma once
#include <stack>
#include "node.h"

using namespace std;

void augmentPipe(pipe* pipe, int value);
int bottleneckValue(vector<pipe*> path);
vector<pipe*> stackToVector(stack<pipe*> stack);
void augmentPath(vector<pipe*> path);
stack<pipe*> pathToAugment(Node* source);

// fills flow network with maximum flowS
void fordFulkerson(Node* source) {
	while (true) {
		try {
			stack<pipe*> pathStack = pathToAugment(source);
			vector<pipe*> path = stackToVector(pathStack);
			augmentPath(path);
		}
		catch (...) {
			return;
		}
	}
}

stack<pipe*> pathToAugment(Node* source) throw (int) {
	stack<pipe*> path;
	Node* current = source;
	while (!current->isSink()) {
		try {
			current = current->goThrough(path);
		}
		catch (...) {
			throw -1; //dead-end, no viable path
		}
	}
	return path;
}

void augmentPath(vector<pipe*> path) {
	int bottleneckVal = bottleneckValue(path);
	for (auto& pipe : path) {
		augmentPipe(pipe, bottleneckVal);
	}
}

vector<pipe*> stackToVector(stack<pipe*> stack) {
	vector<pipe*> vector;
	int size = stack.size();
	for (int i = 0; i < size; i++) {
		vector.push_back(stack.top());
		stack.pop();
	}
	return vector;
}

int bottleneckValue(vector<pipe*> path) {
	int value;
	if (path[0]->pathDir == pathDir_t::toSink) {
		value = path[0]->free();
	}
	else {
		value = path[0]->used;
	}
	for (auto& pipe : path) {
		if (pipe->pathDir == pathDir_t::toSink) {
			if (pipe->free() < value) {
				value = pipe->free();
			}
		}
		else {
			if (pipe->used < value) {
				value = pipe->used;
			}
		}
	}
	return value;
}

void augmentPipe(pipe* pipe, int value) {
	if (pipe->pathDir == pathDir_t::toSink) {
		pipe->used += value;
	}
	else {
		pipe->used -= value;
	}
}