#pragma once
#include "node.h"

class Sink : public Node {
public:
	Sink(int step);

	bool isSink() const override;
};

