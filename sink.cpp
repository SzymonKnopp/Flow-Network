#include "sink.h"

Sink::Sink(std::string name, int step) :
	Node(name, step) {
}

bool Sink::isSink() const {
	return true;
}
