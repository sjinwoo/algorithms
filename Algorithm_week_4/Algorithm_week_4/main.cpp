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
	// print_edges(edges);

	map<string, int> nodes = make_node_index(edges);
	print_nodes(nodes);

	vector<vector<double>> W = makeGraph(edges, nodes);
	vector<vector<double>> D = W;
	vector<vector<int>> P = make_matrix(nodes);
	//floyd(nodes, W, D);
	//print_matrix_dbl(D);
	// print_matrix_dbl(D);

	print_matrix_int(P);

	print_path(nodes, P);

	return 0;
}




