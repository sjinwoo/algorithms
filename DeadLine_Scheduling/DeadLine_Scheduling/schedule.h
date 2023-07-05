#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>
#include <vector>
using namespace std;

class Node {
public:
	Node();									
	Node(string job, int deadline, double wet);
	string get_job() const;
	int get_deadline() const;
	double get_profit() const;
	void set_job(string job);
	void set_deadline(int deadline);
	void set_profit(double profit);
private:
	string job;
	int deadline;	
	double profit;
};

vector<Node> make_node();
vector<Node> read_nodes(const char* fname);
int* make_lst(vector<Node>& nodes);
void print_nodes(vector<Node>& nodes);
void schedule(vector<Node>& nodes, int* J);
int is_feasible(int* J, int deadline);
void print_schedule(vector<Node>& nodes, int* J);

// Solution
typedef struct job {
	int deadline;
	int profit;
} JOB;

#endif