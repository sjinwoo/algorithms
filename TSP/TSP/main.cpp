#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Edge.h"
#include "trim.h"
#include "Tokenizer.h"

int main() {
	const char* fname = "edges.txt";
	vector<Edge> edges = read_edges(fname);
	map<string, int> nodes = make_node_index(edges);

	vector<vector<double>> W = makeGraph(edges, nodes);
	vector<vector<double>> D = makeGraph(nodes);
	vector<vector<int>> P = make_matrix(nodes);
	
	//print_matrix_dbl(W);
	//cout << endl;
	//print_matrix_dbl(D);
	//cout << endl;
	//print_matrix_int(P);
	//cout << endl;

	int min_value = travel(nodes, W, P, D);
	cout << "최소 비용: " << min_value << endl;
	print_path(nodes, P);

	return 0;
}