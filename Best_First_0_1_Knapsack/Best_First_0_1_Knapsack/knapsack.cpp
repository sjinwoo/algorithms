#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <queue>

#include "knapsack.h"
#include "Tokenizer.h"
#include "trim.h"

using namespace std;

Item::Item() {}
Item::Item(string item, int weight, int profit) {
	this->item = item;
	this->weight = weight;
	this->profit = profit;
}
string Item::get_item() const {
	return this->item;
}
int Item::get_weight() const {
	return this->weight;
}
int Item::get_profit() const {
	return this->profit;
}
void Item::set_item(string item) {
	this->item = item;
}
void Item::set_weight(int weight) {
	this->weight = weight;
}
void Item::set_profit(int profit) {
	this->profit = profit;
}

bool Node::operator<(const Node& a) const {
	return this->bound < a.bound;
}
bool Node::operator>(const Node& a) const {
	return this->bound > a.bound;
}

bool CompareFunction(Item& i1, Item& i2) {
	return (double)(i1.get_profit() / i1.get_weight()) > (double)(i2.get_profit() / i2.get_weight());
}

vector<Item> read_items(const char* fname, int& W) {
	vector<Item> items;
	string line;
	ifstream inFile(fname);
	if (!inFile.is_open()) {
		cerr << "Could not open the file - '" << fname << "'" << endl;
		exit(EXIT_FAILURE);
	}
	Tokenizer str;
	string token;
	if (getline(inFile, line)) {
		string _W_ = line;
		W = stoi(_W_);
	}

	while (getline(inFile, line)) {
		str.set(line, "#");
		string item = str.next(); item = trim(item);
		string _weight_ = str.next(); _weight_ = trim(_weight_);
		string _profit_ = str.next(); _profit_ = trim(_profit_);
		int weight = stoi(_weight_);
		int profit = stoi(_profit_);
		items.push_back(Item(item, weight, profit));
	}
	sort(items.begin(), items.end(), CompareFunction);
	return items;
}

void print_items(vector<Item>& items) {
	vector<Item>::iterator it;
	for (it = items.begin(); it != items.end(); ++it) {
		cout << setw(4) << it->get_item() << ", "
			<< setw(3) << it->get_weight() << ", "
			<< setw(3) << it->get_profit() << endl;
	}
}
void knapsack(vector<Item>& items, priority_queue<Node>& pq, int W, int& max_profit) {
	Node v;
	Node u;
	v.bound = bound(items, v, W);
	pq.push(v);
	int include[4] = { 0, };
	while (!pq.empty()) {
		Node v = pq.top(); pq.pop();
		if (v.bound > max_profit) {
			u.level = v.level + 1;
			u.weight = v.weight + items[u.level - 1].get_weight();
			u.profit = v.profit + items[u.level - 1].get_profit();
			if (u.weight <= W && u.profit > max_profit) {
				include[v.level] = 1;
				include[u.level - v.level] = 0;
				max_profit = u.profit;
			}
			u.bound = bound(items, u, W);
			if (u.bound > max_profit)
				pq.push(u);
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(items, u, W);
			if (u.bound > max_profit)
				pq.push(u);
		}
	}
	for (int i = 0; i < items.size(); i++)
		if (include[i]) cout << items[i].get_item() << " ";
	cout << endl << max_profit << endl;
}
int bound(vector<Item>& items, Node& node, int W) {
	if (node.weight >= W) return 0;
	else {
		int result = node.profit;
		int j = node.level + 1;
		int total_weight = node.weight;
		while (j < items.size() && total_weight + items[j - 1].get_weight() <= W) {
			total_weight = total_weight + items[j - 1].get_weight();
			result = result + items[j - 1].get_profit();
			j++;
		}
		int k = j;
		if (k < items.size())
			result = result + (W - total_weight) * items[k - 1].get_profit() / items[k - 1].get_weight();
		return result;
	}
}