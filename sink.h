#pragma once
#include "node.h"

class Sink : public Node {
public:
	Sink(std::string name);

	bool isSink() const override;
};

