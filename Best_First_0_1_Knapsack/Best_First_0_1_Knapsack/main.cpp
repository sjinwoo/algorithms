#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <queue>

#include "knapsack.h"
#include "Tokenizer.h"
#include "trim.h"

using namespace std;

int main() {
	const char* fname = "item2.txt";
	int W;
	vector<Item> items = read_items(fname, W);
	priority_queue<Node> pq;
	int max_profit = 0;
	print_items(items);
	// Best_First
	knapsack(items, pq, W, max_profit);

	return 0;
}