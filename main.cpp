#include "ford-fulkerson.h"
#include "sink.h"

int main() {
	Node* source = new Node(0);
	Node* top = new Node(1);
	Node* bottom = new Node(1);
	Node* sink = new Sink(2);

	source->addOutPipe(top, 3);
	source->addOutPipe(bottom, 1);
	top->addOutPipe(sink, 1);
	top->addOutPipe(bottom, 1);
	bottom->addOutPipe(sink, 3);

	fordFulkerson(source);

	delete source;
	delete top;
	delete bottom;
	delete sink;

	return 0;
}