#include "ford-fulkerson.h"
#include "sink.h"
#include "department.h"
#include "group.h"
#include "flowNetwork.h"
#include <iostream>
#include <vector>

using namespace std;

void writeResearcherTask(Node* taskNode, int& taskCount, string& schedule);
void writeResearcherTime(Node* timeNode, int& taskCount, string& schedule);
void writeResearcherDay(Node* dayNode, int& taskCount, string& schedule);
void writeResearcherSchedule(string name, FlowNetwork& flowNetwork);
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

	if (outputMode == 2) { //fill flow network once again, simulate solution, so that informations about researcher schedules can be extracted
		for (int dep = 0; dep < departmentCount; dep++) {
			for (int res = 0; res < researchersFromDepartments[dep]; res++) {
				/*try {
					flowNetwork.activateResearcher(departments[dep].researchers[res].name);
				}
				catch (...) {
					cout << "Error: researcher named " << departments[dep].researchers[res].name << " not found in flow network." << endl;
					return false;
				}*/ //STOS terminating execution on error
				flowNetwork.activateResearcher(departments[dep].researchers[res].name);
			}
		}
		fordFulkerson(flowNetwork.getSource());
	}
	cout << activeResearchersValue(researchersFromDepartments, departments, departmentCount) << endl;
	for (int dep = 0; dep < departmentCount; dep++) {
		if(researchersFromDepartments[dep] != 0){
			cout << departments[dep].name << " " << researchersFromDepartments[dep] << endl;
		}
		if (outputMode == 2) {
			for (int res = 0; res < researchersFromDepartments[dep]; res++) {
				writeResearcherSchedule(departments[dep].researchers[res].name, flowNetwork);
			}
		}
	}

	delete[] researchersFromDepartments;
	delete[] departments;
	delete[] groups;

	return 0;
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
			/*try {
				flowNetwork.activateResearcher(departments[dep].researchers[res].name);
			}
			catch (...) {
				cout << "Error: researcher named " << departments[dep].researchers[res].name << " not found in flow network." << endl;
				return false;
			}*/ //STOS terminating execution on error
			flowNetwork.activateResearcher(departments[dep].researchers[res].name);
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

void writeResearcherSchedule(string name, FlowNetwork& flowNetwork) {
	Node* researcherNode;
	try {
		researcherNode = flowNetwork.getResearcher(name);
	}
	catch (int) {
		cerr << "Error: Researcher not found";
		return;
	}
	int taskCount = 0;
	string schedule = "";
	for (auto& pipe : researcherNode->pipesOut) {
		if (pipe->used != 0) {
			writeResearcherDay(pipe->sink, taskCount, schedule);
		}
	}
	cout << name << " " << taskCount << endl << schedule;
}
void writeResearcherDay(Node* dayNode, int& taskCount, string& schedule) {
	for (auto& pipe : dayNode->pipesOut) {
		if (pipe->used != 0) {
			writeResearcherTime(pipe->sink, taskCount, schedule);
		}
	}
}
void writeResearcherTime(Node* timeNode, int& taskCount, string& schedule) {
	for (auto& pipe : timeNode->pipesOut) {
		if (pipe->used != 0) {
			writeResearcherTask(pipe->sink, taskCount, schedule);
		}
	}
}
void writeResearcherTask(Node* taskNode, int& taskCount, string& schedule) {
	TaskNode* taskCast = dynamic_cast<TaskNode*>(taskNode);
	string groupName;
	for (auto& pipe : taskNode->pipesOut) {
		if (pipe->sink->name != "sink") {
			groupName = pipe->sink->name;
			break;
		}
	}
	taskCount++;
	schedule += groupName + ' ';
	schedule += (char)(taskCast->day + '0');
	schedule += ' ';
	schedule += (char)(taskCast->time + '0');
	schedule += '\n';
}