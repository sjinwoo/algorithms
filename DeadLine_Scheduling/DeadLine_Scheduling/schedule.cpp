#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "schedule.h"
#include "Tokenizer.h"
#include "trim.h"
using namespace std;

Node::Node() {}
Node::Node(string job, int deadline, double profit) {
	this->job = job;
	this->deadline = deadline;
	this->profit = profit;
}
string Node::get_job() const {
	return this->job;
}
int Node::get_deadline() const {
	return this->deadline;
}
double Node::get_profit() const {
	return this->profit;
}
void Node::set_job(string job) {
	this->job = job;
}
void Node::set_deadline(int deadline) {
	this->deadline = deadline;
}
void Node::set_profit(double profit) {
	this->profit = profit;
}
vector<Node> make_node() {
	vector<Node> res;
	res.push_back(Node("J1", 3, 40));
	res.push_back(Node("J2", 1, 35));
	res.push_back(Node("J3", 1, 30));
	res.push_back(Node("J4", 3, 25));
	res.push_back(Node("J5", 1, 20));
	res.push_back(Node("J6", 3, 15));
	res.push_back(Node("J7", 2, 10));
	return res;
}

bool CompareFunction(const Node& e1, const Node& e2) {
	return e1.get_profit() > e2.get_profit();
}

vector<Node> read_nodes(const char* fname) {
	vector<Node> nodes;
	string line;
	ifstream inFile(fname);
	if (!inFile.is_open()) {
		cerr << "Could not open the file - '" << fname << "'" << endl;
		exit(EXIT_FAILURE);
	}
	Tokenizer str;
	string token;
	while (getline(inFile, line)) {
		str.set(line, "#");
		string job = str.next(); job = trim(job);
		string _deadline_ = str.next(); _deadline_ = trim(_deadline_);
		string _profit_ = str.next(); _profit_ = trim(_profit_);
		int deadline = atoi(_deadline_.c_str());
		double profit = atof(_profit_.c_str());
		nodes.push_back(Node(job, deadline, profit));
	}
	return nodes;
}

int* make_lst(vector<Node>& nodes) {
	int* J = new int[nodes.size() + 1];
	for (int i = 0; i < nodes.size(); i++) J[i] = -1;
	return J;
}

void print_nodes(vector<Node>& nodes) {
	vector<Node>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it) {
		cout << it->get_job() << ", "
			<< it->get_deadline() << ", "
			<< it->get_profit() << endl;
	}
}

void schedule(vector<Node>& nodes, int* J) {
	sort(nodes.begin(), nodes.end(), CompareFunction);
	J[nodes[0].get_deadline()] = 0;
	for (int i = 1; i < nodes.size(); i++) {
		int location = is_feasible(J, nodes[i].get_deadline());
		if (location > -1) J[location] = i;
	}
}

int is_feasible(int* J, int deadline) {
	for (int location = deadline; location > 0; location--) {
		if (J[location] < 0) return location;
	}
	return -1;
}

void print_schedule(vector<Node>& nodes, int* J) {
	for (int i = 0; i < nodes.size(); i++)
		if (J[i] > -1)
			cout << nodes[J[i]].get_job() << "  ";
	cout << endl;
}