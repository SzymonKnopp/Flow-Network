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

	for (int i = 0; i < tasks.size(); i++) {
		connectTaskToTimes(tasks[i]);
	}
}
FlowNetwork::~FlowNetwork() {
	deleteSource();
	deleteSink();
}

void FlowNetwork::activateResearcher(string name) throw (int) {
	for (auto& researcher : researchers) {
		if (researcher->name == name) {
			researcher->active = true;
			return;
		}
	}
	throw -1;
}

void FlowNetwork::deactivateResearchers() {
	for (auto& researcher : researchers) {
		researcher->active = false;
	}
}

bool FlowNetwork::sinkMaxFilled() {
	for (auto& pipe : sink->pipesIn) {
		if (pipe->used != pipe->capacity) {
			return false;
		}
	}
	return true;
}

void FlowNetwork::clearFlow() {
	clearBranch(source);
}
void FlowNetwork::clearBranch(Node* current) {
	for (auto& pipe : current->pipesOut) {
		pipe->used = 0;
		clearBranch(pipe->sink);
	}
}

Node* FlowNetwork::getSource() const {
	return source;
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
	researcherNode->active = false;
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

void FlowNetwork::connectTaskToTimes(TaskNode* taskNode) {
	for (int i = 0; i < researchers.size(); i++) {
		Node* current = researchers[i];
		current = current->pipesOut[taskNode->day - 1]->sink;
		current = current->pipesOut[taskNode->time - 1]->sink;
		current->addOutPipe(taskNode, 1);
	}
}

void FlowNetwork::deleteSource() {
	for (int i = 0; i < source->pipesOut.size(); i++) {
		deleteResearcher(source->pipesOut[i]->sink);
	}
	delete source;
}
void FlowNetwork::deleteResearcher(Node* researcherNode) {
	for (int i = 0; i < researcherNode->pipesOut.size(); i++) {
		deleteDay(researcherNode->pipesOut[i]->sink);
	}
	delete researcherNode;
}
void FlowNetwork::deleteDay(Node* dayNode) {
	for (int i = 0; i < dayNode->pipesOut.size(); i++) {
		delete dayNode->pipesOut[i]->sink;
	}
	delete dayNode;
}
void FlowNetwork::deleteSink() {
	for (int i = 0; i < sink->pipesIn.size(); i++) {
		delete sink->pipesIn[i]->source;
	}
	delete sink;
}

int FlowNetwork::max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}
