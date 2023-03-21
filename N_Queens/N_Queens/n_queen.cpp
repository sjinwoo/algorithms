#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "n_queen.h"
using namespace std;

vector<int> make_list(int n) {
	vector<int> col(n + 1, 0);
	return col;
}

void queens(int i, vector<int>& col) {
	if (promising(i, col)) {
		if (i == col.size() - 1)
			print_list(col);
		else {
			for (int j = 1; j <= col.size() - 1; j++) {
				col[i + 1] = j;
				queens(i + 1, col);
			}
		}
	}
}

bool promising(int i, vector<int>& col) {
	bool st = true;
	int k = 1;
	while (k < i && st) {
		if (col[i] == col[k] || abs(col[i] - col[k]) == i - k) st = false;
		k++;
	}
	return st;
}

void print_list(vector<int>& col) {
	for (int i = 1; i < col.size(); i++)
		cout << col[i] << " ";
	cout << endl;
}