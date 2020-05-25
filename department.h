#pragma once
#include <string>
#include "researcher.h"

class Department {
public:
	Department();
	~Department();

	std::string name;
	int researcherCount;
	researcher* researchers;

private:
	researcher newResearcher();
};