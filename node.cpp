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

Node* Node::goThrough(std::vector<pipe*>& path) const {
	for (auto& pipe : _pipesOut) {
		if (pipe->free() != 0 && this->_step <= pipe->sink->_step) {
			pipe->flowDir = flowDir_t::toSink;
			path.push_back(pipe);
			return pipe->sink;
		}
	}
	for (auto& pipe : _pipesIn) {
		if (pipe->used != 0 && this->_step <= pipe->source->_step) {
			pipe->flowDir = flowDir_t::toSource;
			path.push_back(pipe);
			return pipe->source;
		}
	}
}
