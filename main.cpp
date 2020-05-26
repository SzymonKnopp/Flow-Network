#include "ford-fulkerson.h"
#include "sink.h"
#include "department.h"
#include "group.h"
#include "flowNetwork.h"
#include <iostream>
#include <vector>

using namespace std;

void nextIteration(int*& iteration, int iterSize, Department* departments);
bool solvesFlowNetwork(FlowNetwork& flowNetwork, int*& iterations, Department* departments, int departmentCount);
void solve(FlowNetwork& flowNetwork, Department* departments, int departmentCount);

int main() {
	int schedulingMode;
	int newDayLimit = NULL;
	cin >> schedulingMode;
	if (schedulingMode == 3) {
		cin >> newDayLimit;
	}

	int outputMode;
	cin >> outputMode;

	int departmentCount;
	cin >> departmentCount;
	Department* departments = new Department[departmentCount];

	int groupCount;
	cin >> groupCount;
	Group* groups = new Group[groupCount];

	FlowNetwork flowNetwork(departments, departmentCount, groups, groupCount);

	

	return 0;

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
}

void solve(FlowNetwork& flowNetwork, Department* departments, int departmentCount) {
	vector<int*> solutions;

	int iterations = 1;
	for (int i = 0; i < departmentCount; i++) {
		iterations *= departments[i].researcherCount;
	}
	int* iteration = new int[departmentCount] {};
	for (int i = 0; i < iterations; i++) {
		if (solvesFlowNetwork(flowNetwork, iteration, departments, departmentCount)) {
			solutions.push_back(iteration);
		}
		nextIteration(iteration, departmentCount, departments);
	}
}

bool solvesFlowNetwork(FlowNetwork& flowNetwork, int*& iterations, Department* departments, int departmentCount) {
	
}

void nextIteration(int*& iteration, int iterSize, Department* departments) {
	(iteration[0])++;
	for (int i = 0; i < iterSize - 1; i++) {
		if (iteration[i] == departments[i].researcherCount) {
			(iteration[i + 1])++;
			iteration[i] = 0;
		}
	}
}