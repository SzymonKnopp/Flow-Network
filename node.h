#pragma once
#include "pipe.h"
#include <vector>

class Node {
public:

private:
	std::vector<pipe*> pipesIn;
	std::vector<pipe*> pipesOut;
};

