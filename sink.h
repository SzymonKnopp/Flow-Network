#pragma once
#include "node.h"

class Sink : public Node {
public:
	Sink(std::string name, int step);

	bool isSink() const override;
};

