#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include "knapsack.h"
#include "Tokenizer.h"
#include "trim.h"
using namespace std;

int main() {
	const char* fname = "item2.txt";
	int W;
	vector<Item> items = read_items(fname, W);
	print_items(items);
	// Bound
	vector<int> bestset(items.size(), 0);
	knapsack(items, W, -1, 0, 0, bestset);
	print_knapsack(items, bestset);

	return 0;
} 