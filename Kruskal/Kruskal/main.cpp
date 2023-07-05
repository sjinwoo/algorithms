#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

#include "Edge.h"
#include "trim.h"
#include "Tokenizer.h"

using namespace std;

int main() {
	const char* fname = "edges.txt";
	vector<Edge> E = read_edges(fname);
	map<string, int> nodes = make_node_index(E);
	vector<Edge> F;
	int *U = new int[nodes.size() + 1];

	kruskal(nodes.size(), E.size(), nodes, E, F, U);

	print_edges(F);

	delete[] U;
	return 0;
}

