#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <string>
#include <vector>
using namespace std;

class Item {
public:
	Item();									
	Item(string item, int weight, int profit);
	string get_item() const;
	int get_weight() const;
	int get_profit() const;
	void set_item(string item);
	void set_weight(int weight);
	void set_profit(int profit);
private:
	string item;
	int weight;
	int profit;
};

class Node {
public:
	int level;
	int profit;
	int weight;
	int bound;
	int state;
	Node() {
		this->level = 0;
		this->profit = 0;
		this->weight = 0;
		this->bound = 0;
		this->state = 0;
	}
	bool operator<(const Node& a) const;
	bool operator>(const Node& a) const;
};

vector<Item> read_items(const char* fname, int& W);
void print_items(vector<Item>& items);
void knapsack(vector<Item>& items, priority_queue<Node>& pq, int W, int& max_profit);
int bound(vector<Item>& items, Node& node, int W);

#endif