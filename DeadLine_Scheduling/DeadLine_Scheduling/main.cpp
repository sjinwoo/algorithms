#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include "schedule.h"
#include "Tokenizer.h"
#include "trim.h"
using namespace std;

int feasible(int J[], int deadline);
void schedule_s(int n, JOB jobs[], int J[]);
void print_job_s(int J[]);

int main() {
	//Answer
	const char* fname = "nodes.txt";
	vector<Node> nodes = read_nodes(fname);
	print_nodes(nodes);
	int* J = make_lst(nodes);
	schedule(nodes, J);
	print_schedule(nodes, J);
	delete[] J;

	//// Solution
	//JOB jobs[] = { {3, 40}, {1, 35}, {1, 30}, {3, 25}, {1, 20}, {3, 15}, {2, 10} };
	//int n = 7;
	//int J[8];
	//for (int i = 0; i < n + 1; i++) J[i] = -1;
	//schedule_s(n, jobs, J);
	//print_job_s(J);
	return 0;
}

int feasible(int J[], int deadline) {
	for (int loc = deadline; loc > 0; loc--) {
		// 비어 있다면,
		if (J[loc] < 0) return loc;
	}
	return -1;
}
void schedule_s(int n, JOB jobs[], int J[]) {
	// deadline 번 째 index에 채움.
	J[jobs[0].deadline] = 0;
	// Check feasible
	for (int i = 1; i < n; i++) {
		// feasible() 은 index를 반환, 없으면 -1
		int loc = feasible(J, jobs[i].deadline);
		if (loc >= 0)
			J[loc] = i;
	}
}
void print_job_s(int J[]) {
	int idx = 1;
	while (J[idx] >= 0) {
		cout << J[idx] + 1 << "  ";
		idx++;
	}
	cout << endl;
}