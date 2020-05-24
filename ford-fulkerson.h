#pragma once
#include "node.h"

using namespace std;

void augmentPipe(pipe* pipe, int value);
int bottleneckValue(vector<pipe*> path);
void augmentPath(vector<pipe*> path);
bool foundPath(vector<pipe*>& path, Node* node);
vector<pipe*> pathToAugment(Node* source) throw (int);

// fills flow network with maximum flow
void fordFulkerson(Node* source) {
	while (true) {
		try {
			vector<pipe*> path = pathToAugment(source);
			augmentPath(path);
		}
		catch (...) {
			return;
		}
	}
}

vector<pipe*> pathToAugment(Node* source) throw (int) {
	vector<pipe*> path;
	if (foundPath(path, source)) {
		return path;
	}
	else {
		throw -1; //viable path not found
	}
}

bool foundPath(vector<pipe*>& path, Node* node) {
	if (node->isSink()) {
		return true;
	}
	for (auto& pipe : node->pipesOut) {
		if (pipe->free() != 0
			&& node->step <= pipe->sink->step &&
			foundPath(path, pipe->sink)) {
				pipe->pathDir = pathDir_t::toSink;
				path.push_back(pipe);
				return true;
		}
	}
	for (auto& pipe : node->pipesIn) {
		if (pipe->used != 0
			&& node->step <= pipe->source->step &&
			foundPath(path, pipe->source)) {
				pipe->pathDir = pathDir_t::toSource;
				path.push_back(pipe);
				return true;
		}
	}
	return false;
}

void augmentPath(vector<pipe*> path) {
	int bottleneckVal = bottleneckValue(path);
	for (auto& pipe : path) {
		augmentPipe(pipe, bottleneckVal);
	}
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