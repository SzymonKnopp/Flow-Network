#pragma once
#include <vector>
#include "department.h"
#include "group.h"
#include "researcher.h"
#include "sink.h"
#include "taskNode.h"
#include <string>

using namespace std;

class FlowNetwork {
public:
	FlowNetwork(Department* departments, int departmentCount, Group* groups, int groupCount);
	~FlowNetwork();

	void activateResearcher(string name) throw (int);
	void deactivateResearchers();
	bool sinkMaxFilled();
	void clearFlow();
	Node* getSource() const;

private:
	int days;
	int times;
	Node* source;
	vector<Node*> researchers;
	vector<TaskNode*> tasks;
	Node* sink;

	void makeGroupTask(Group& group);
	void makeTask(task& task, Node* groupNode);
	void makeResearchers(Department& department);
	void makeResearcherDayTime(researcher& researcher);
	void makeDayTime(researcher& researcher, Node* researcherNode);
	void makeTime(Node* dayNode);
	void connectTaskToTimes(TaskNode* taskNode);
	void clearBranch(Node* current);
	void deleteSource();
	void deleteResearcher(Node* researcherNode);
	void deleteDay(Node* dayNode);
	void deleteSink();
	

	static int max(int a, int b);
};

