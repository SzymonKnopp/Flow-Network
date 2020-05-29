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
		/*try {
			vector<pipe*> path = pathToAugment(source);
			augmentPath(path);
		}
		catch (...) {
			return;
		}*/ //STOS terminating execution on error
		vector<pipe*> path = pathToAugment(source);
		if (path.size() != 0) {
			augmentPath(path);
		}
		else {
			return;
		}
	}
}

vector<pipe*> pathToAugment(Node* source) throw (int) {
	vector<pipe*> path;
	/*if (foundPath(path, source)) {
		return path;
	}
	else {
		throw -1; //viable path not found
	}*/ //STOS terminating execution on error
	if (foundPath(path, source)) {
		return path;
	}
	else {
		vector<pipe*> emptyPath;
		return emptyPath;
	}
}

bool foundPath(vector<pipe*>& path, Node* node) {
	if (node->isSink()) {
		return true;
	}
	node->usedInPath = true;
	for (auto& pipe : node->pipesOut) {
		if (pipe->free() != 0
			&& pipe->sink->usedInPath == false
			&& pipe->sink->active == true
			&& foundPath(path, pipe->sink)) {
				pipe->pathDir = pathDir_t::toSink;
				path.push_back(pipe);
				node->usedInPath = false;
				return true;
		}
	}
	for (auto& pipe : node->pipesIn) {
		if (pipe->used != 0
			&& pipe->source->usedInPath == false
			&& pipe->source->active == true
			&& foundPath(path, pipe->source)) {
				pipe->pathDir = pathDir_t::toSource;
				path.push_back(pipe);
				node->usedInPath = false;
				return true;
		}
	}
	node->usedInPath = false;
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