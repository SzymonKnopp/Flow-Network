#pragma once
#include <vector>
#include "department.h"
#include "group.h"
#include "researcher.h"
#include "sink.h"

using namespace std;

class FlowNetwork {
public:
	FlowNetwork(Department* departments, int departmentCount, Group* groups, int groupCount);
	~FlowNetwork();



private:
	int days;
	int times;
	Node* source;
	vector<Node*> researchers;
	vector<Node*> tasks;
	Node* sink;

	void makeGroupTask(Group& group);
	void makeTask(task& task, Node* groupNode);
	void makeResearchers(Department& department);
	void makeResearcherDayTime(researcher& researcher);
	void makeDayTime(researcher& researcher, Node* researcherNode);
	void makeTime(Node* dayNode);

	static int max(int a, int b);
};

