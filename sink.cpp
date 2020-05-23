#include "sink.h"

Sink::Sink(int step) :
	Node(step) {
}

bool Sink::isSink() const {
	return true;
}
