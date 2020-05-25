#include "department.h"
#include <iostream>

using namespace std;

Department::Department() {
	cin >> name;
	cin >> researcherCount;
	researchers = new researcher[researcherCount];
	for (int i = 0; i < researcherCount; i++) {
		researchers[i] = newResearcher();
	}
}
Department::~Department() {
	delete[] researchers;
}

researcher Department::newResearcher() {
	researcher newResearcher;
	cin >> newResearcher.name;
	cin >> newResearcher.value;
	cin >> newResearcher.limit;
	cin >> newResearcher.dayLimit;
	return newResearcher;
}
