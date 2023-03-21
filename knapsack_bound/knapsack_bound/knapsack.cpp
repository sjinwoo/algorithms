#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

#include "knapsack.h"
#include "Tokenizer.h"
#include "trim.h"
using namespace std;

int maxprofit = 0;
int numbest = 0;
vector<int> include(4, 0);

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
void knapsack(vector<Item>& items, int W, int idx, int profit, int weight, vector<int>& bestset) {
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = idx;
		bestset = include;
	}
	if (promising(items, W, idx, profit, weight)) {
		include[idx + 1] = 1;
		knapsack(items, W, idx + 1, profit + items[idx + 1].get_profit(), weight + items[idx + 1].get_weight(), bestset);
		include[idx + 1] = 0;
		knapsack(items, W, idx + 1, profit, weight, bestset);
	}
}

bool promising(vector<Item>& items, int W, int idx, int profit, int weight) {
	int j, k;
	int total_weight;
	float bound;

	if (weight >= W) return false;
	else {
		j = idx + 1;
		bound = profit;
		total_weight = weight;

		while ((j < items.size()) && ((total_weight + items[j].get_weight()) <= W)) {
			total_weight = total_weight + items[j].get_weight();
			bound = bound + items[j].get_profit();
			j++;
		}
		k = j;
		if (k < items.size()) bound = bound + (W + total_weight) * items[k].get_profit() / items[k].get_weight();
		return bound > maxprofit;
	}
}

void print_knapsack(vector<Item>& items, vector<int>& bestset) {
	cout << maxprofit << endl;;
	for (int i = 0; i < items.size(); i++) {
		if (bestset[i] == 1)
			cout << items[i].get_item() << ", ";
	}
	cout << endl;
}