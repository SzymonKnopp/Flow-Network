#include "node.h"

Node::Node(int step) :
	_step(step)
{}

void Node::addOutPipe(Node* sink, int capacity) {
	pipe* newPipe = new pipe();
	newPipe->capacity = capacity;
	newPipe->source = this;
	newPipe->sink = sink;

	this->_pipesOut.push_back(newPipe);
	sink->_pipesIn.push_back(newPipe);
}

Node* Node::goThrough() const {
	for (auto& pipe : _pipesOut) {
		if (pipe->free() != 0 && this->_step <= pipe->sink->_step) {
			return pipe->sink;
		}
	}
	for (auto& pipe : _pipesIn) {
		if (pipe->used != 0 && this->_step <= pipe->source->_step) {
			return pipe->source;
		}
	}
}
