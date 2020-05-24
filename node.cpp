#include "node.h"

Node::Node(int step) :
	step(step) {
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

//Node* Node::goThrough(std::stack<pipe*>& path) const throw (int) {
//	for (auto& pipe : _pipesOut) {
//		if (pipe->free() != 0 && this->_step <= pipe->sink->_step) {
//			pipe->pathDir = pathDir_t::toSink;
//			path.push(pipe);
//			return pipe->sink;
//		} 
//	}
//	for (auto& pipe : _pipesIn) {
//		if (pipe->used != 0 && this->_step <= pipe->source->_step) {
//			pipe->pathDir = pathDir_t::toSource;
//			path.push(pipe);
//			return pipe->source;
//		}
//	}
//	throw -1; //couldn't find viable pipe to go through
//}
