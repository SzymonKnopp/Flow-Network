#include "taskNode.h"
#include "flowNetwork.h"

FlowNetwork::FlowNetwork(Department* departments, int departmentCount, Group* groups, int groupCount) {
	days = 0;
	times = 0;
	sink = new Sink("sink", 6);
	for (int i = 0; i < groupCount; i++) {
		makeGroupTask(groups[i]);
	}

	source = new Node("source", 0);
	for (int i = 0; i < departmentCount; i++) {
		makeResearchers(departments[i]);
	}
}
FlowNetwork::~FlowNetwork() {
	//TODO
}

void FlowNetwork::makeGroupTask(Group& group) {
	Node* groupNode = new Node(group.name, 5);
	groupNode->addOutPipe(sink, group.groupHours);
	for (int i = 0; i < group.taskCount; i++) {
		makeTask(group.tasks[i], groupNode);
	}
}

void FlowNetwork::makeTask(task& task, Node* groupNode) {
	days = max(days, task.day);
	times = max(times, task.time);
	TaskNode* taskNode = new TaskNode("task", 4);
	taskNode->day = task.day;
	taskNode->time = task.time;
	taskNode->addOutPipe(sink, task.minHours);
	taskNode->addOutPipe(groupNode, task.maxHours - task.minHours);
	tasks.push_back(taskNode);
}

void FlowNetwork::makeResearchers(Department& department) {
	for (int i = 0; i < department.researcherCount; i++) {
		makeResearcherDayTime(department.researchers[i]);
	}
}

void FlowNetwork::makeResearcherDayTime(researcher& researcher) {
	Node* researcherNode = new Node(researcher.name, 1);
	researchers.push_back(researcherNode);
	source->addOutPipe(researcherNode, researcher.limit);
	for (int i = 0; i < days; i++) {
		makeDayTime(researcher, researcherNode);
	}
}
void FlowNetwork::makeDayTime(researcher& researcher, Node* researcherNode) {
	Node* dayNode = new Node("day", 2);
	researcherNode->addOutPipe(dayNode, researcher.dayLimit);
	for (int i = 0; i < times; i++) {
		makeTime(dayNode);
	}
}
void FlowNetwork::makeTime(Node* dayNode) {
	Node* timeNode = new Node("time", 3);
	dayNode->addOutPipe(timeNode, 1);
}

int FlowNetwork::max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}
