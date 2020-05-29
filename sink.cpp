#include "sink.h"

Sink::Sink(std::string name) :
	Node(name) {
}

bool Sink::isSink() const {
	return true;
}