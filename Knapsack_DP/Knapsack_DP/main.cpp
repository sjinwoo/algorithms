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
	const char* fname = "test.txt";
	int result1, result2, W;
	vector<Item> items = read_items(fname, W);
	print_items(items);

	// DP
	vector<vector<int>> P = make_matrix(items, W);
	double runtime1 = knapsack_DP(items, P, W, result1);

	// Greedy
	double runtime2 = knapsack_GD(items, W, result2);
	
	// Bound


	cout << setprecision(16);
	cout << "Greedy Algorithm : " << runtime2 << endl;
	cout << "Dynamic Algorithm : " << runtime1 << endl;
	cout << "Solutions" << endl << "--------------" << endl;
	cout << "Greedy" << endl << result2 << endl;
	cout << "--------------" << endl;
	cout << "Dynamic Programming" << endl << result1 << endl;

	return 0;
} 