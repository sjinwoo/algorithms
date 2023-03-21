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
	return items;
}

void print_items(vector<Item>& items) {
	vector<Item>::iterator it;
	for (it = items.begin(); it != items.end(); ++it) {
		cout << setw(10) << it->get_item() << ", "
			<< setw(3) << it->get_weight() << ", "
			<< setw(3) << it->get_profit() << endl;
	}
}

vector<vector<int>> make_matrix(vector<Item>& items, int knapsack) {
	vector<vector<int>> matrix;
	for (int i = 0; i <= items.size(); i++) {
		vector<int> row(knapsack + 1, 0);
		matrix.push_back(row);
	}
	return matrix;
}

void print_matrix(vector<vector<int>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) cout << matrix[i][j] << setw(4);
		cout << endl;
	}
}

double knapsack_DP(vector<Item>& items, vector<vector<int>>& P, int W, int& result1) {
	clock_t start = clock();
	for (int t = 0; t < 10000; t++) {
		for (int i = 0; i < items.size(); i++) {
			for (int j = 1; j <= W; j++) {
				if (items[i].get_weight() <= j)
					P[i + 1][j] = max(P[i][j], items[i].get_profit() + P[i][j - items[i].get_weight()]);
				else P[i + 1][j] = P[i][j];
			}
		}
		result1 = P[items.size()][W];
	}
	clock_t end = clock();
	return double(end - start) / CLOCKS_PER_SEC / 10000;
}

double knapsack_GD(vector<Item>& items, int W, int& result2) {
	clock_t start = clock();
	sort(items.begin(), items.end(), CompareFunction);
	for (int t = 0; t < 10000; t++) {
		int curr_W = 0;
		result2 = 0;
		for (int i = 0; i < items.size(); i++) {
			if ((curr_W + items[i].get_weight()) > W) break;
			curr_W += items[i].get_weight();
			result2 += items[i].get_profit();
		}
	}
	clock_t end = clock();
	return double(end - start) / CLOCKS_PER_SEC / 10000;
}

//void knapsack_BD(vector<Item>& items, int W)
