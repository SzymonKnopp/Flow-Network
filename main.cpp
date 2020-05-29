#include "ford-fulkerson.h"
#include "sink.h"
#include "department.h"
#include "group.h"
#include "flowNetwork.h"
#include <iostream>
#include <vector>

using namespace std;

int activeResearchersValue(int* solution, Department* departments, int departmentCount);
int* lowestValueSolution(vector<int*> solutions, Department* departments, int departmentCount);
void nextIteration(int*& iteration, int iterSize, Department* departments);
int* copyArray(int* original, int size);
bool solvesFlowNetwork(FlowNetwork& flowNetwork, int*& iterations, Department* departments, int departmentCount);
int* solution(FlowNetwork& flowNetwork, Department* departments, int departmentCount);

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

	int* researchersFromDepartments = solution(flowNetwork, departments, departmentCount);

	cout << activeResearchersValue(researchersFromDepartments, departments, departmentCount) << endl;
	for (int i = 0; i < departmentCount; i++) {
		cout << departments[i].name << " " << researchersFromDepartments[i] << endl;
	}

	delete[] researchersFromDepartments;
	delete[] departments;
	delete[] groups;

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

int* solution(FlowNetwork& flowNetwork, Department* departments, int departmentCount) {
	vector<int*> solutions;
	int iterations = 1;
	for (int i = 0; i < departmentCount; i++) {
		iterations *= departments[i].researcherCount + 1;
	}
	int* iteration = new int[departmentCount] {};
	for (int i = 0; i < iterations; i++) {
		if (solvesFlowNetwork(flowNetwork, iteration, departments, departmentCount)) {
			solutions.push_back(copyArray(iteration, departmentCount));
		}
		nextIteration(iteration, departmentCount, departments);
	}
	delete[] iteration;
	int* solution = copyArray(lowestValueSolution(solutions, departments, departmentCount), departmentCount);
	for (auto& solution : solutions) {
		delete[] solution;
	}
	return solution;
}

bool solvesFlowNetwork(FlowNetwork& flowNetwork, int*& iterations, Department* departments, int departmentCount) {
	for (int dep = 0; dep < departmentCount; dep++) {
		for (int res = 0; res < iterations[dep]; res++) {
			try {
				flowNetwork.activateResearcher(departments[dep].researchers[res].name);
			}
			catch (...) {
				cout << "Error: researcher named " << departments[dep].researchers[res].name << " not found in flow network." << endl;
				return false;
			}
		}
	}

	fordFulkerson(flowNetwork.getSource());

	bool solves = flowNetwork.sinkMaxFilled();
	flowNetwork.clearFlow();
	flowNetwork.deactivateResearchers();

	return solves;
}

int* copyArray(int* original, int size) {
	int* copy = new int[size];
	for (int i = 0; i < size; i++) {
		copy[i] = original[i];
	}
	return copy;
}

void nextIteration(int*& iteration, int iterSize, Department* departments) {
	(iteration[0])++;
	for (int i = 0; i < iterSize - 1; i++) {
		if (iteration[i] == departments[i].researcherCount + 1) {
			(iteration[i + 1])++;
			iteration[i] = 0;
		}
	}
}

int* lowestValueSolution(vector<int*> solutions, Department* departments, int departmentCount) {
	int* solution = solutions[0];
	int solutionValue = activeResearchersValue(solutions[0], departments, departmentCount);
	for (int i = 1; i < solutions.size(); i++) {
		int newValue = activeResearchersValue(solutions[i], departments, departmentCount);
		if (newValue < solutionValue) {
			solutionValue = newValue;
			solution = solutions[i];
		}
	}
	return solution;
}

int activeResearchersValue(int* solution, Department* departments, int departmentCount) {
	int value = 0;
	for (int dep = 0; dep < departmentCount; dep++) {
		for (int res = 0; res < solution[dep]; res++) {
			value += departments[dep].researchers[res].value;
		}
	}
	return value;
}