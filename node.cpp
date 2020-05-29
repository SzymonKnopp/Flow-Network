#include "node.h"

Node::Node(std::string name) :
	name(name),
	active(true),
	usedInPath(false) {
}

Node::~Node() {
	for (auto& pipe : pipesOut) {
		delete pipe;
	}
}

void Node::addOutPipe(Node* sink, int capacity) {
	pipe* newPipe = new pipe();
	newPipe->capacity = capacity;
	newPipe->source = this;
	newPipe->sink = sink;

	this->pipesOut.push_back(newPipe);
	sink->pipesIn.push_back(newPipe);
}

bool Node::isSink() const {
	return false;
}