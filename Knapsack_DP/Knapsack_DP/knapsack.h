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

vector<Item> read_items(const char* fname, int& W);
void print_items(vector<Item>& items);
vector<vector<int>> make_matrix(vector<Item>& items, int knapsack);
void print_matrix(vector<vector<int>>& matrix);
double knapsack_DP(vector<Item>& items, vector<vector<int>>& P, int W, int& result1);
double knapsack_GD(vector<Item>& items, int W, int& result2);

#endif