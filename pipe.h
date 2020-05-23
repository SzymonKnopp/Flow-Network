#pragma once

class Node;

enum class flowDir_t { toSource = -1, toSink = 1 };

struct pipe {

	Node* source = nullptr;
	Node* sink = nullptr;
	int capacity = 0;
	int used = 0;
	flowDir_t flowDir;

	int free() {
		return capacity - used;
	}
};