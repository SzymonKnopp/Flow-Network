#include "ford-fulkerson.h"
#include "sink.h"

int main() {



	//DEBUG
	Node* source = new Node("source", 0);
	Node* top = new Node("top", 1);
	Node* bottom = new Node("bottom", 1);
	Node* sink = new Sink("sink", 2);

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