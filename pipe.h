#pragma once

class Node;

struct pipe {
	Node* source = nullptr;
	Node* sink = nullptr;
	int capacity = 0;
	int used = 0;
};