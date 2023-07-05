#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "n_queen.h"
using namespace std;

int main() {
	const int n = 8;
	vector<int> col = make_list(n);
	queens(0, col);

	return 0;
}