#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdlib.h>

#include "Edge.h"
#include "Tokenizer.h"
#include "trim.h"
using namespace std;

Edge::Edge() {}

Edge::Edge(string _fr_, string _to_, double _wet_) {
	fr = _fr_;
	to = _to_;
	wet = _wet_;
}
string Edge::get_fr() const {
	return fr;
}
string Edge::get_to() const {
	return to;
}
double Edge::get_wet() const {
	return wet;
}
void Edge::set_fr(string _fr_) {
	fr = _fr_;
}
void Edge::set_to(string _to_) {
	to = _to_;
}
void Edge::set_wet(double _wet_) {
	wet = _wet_;
}

vector<Edge> read_edges(const char* fname) {
	vector<Edge> edges;
	string line;
	ifstream inFile(fname);

	if (!inFile.is_open()) {
		cerr << "Could not open the file - '" << fname << "'" << endl;
		exit(EXIT_FAILURE);
	}

	Tokenizer str;
	string token;

	while (getline(inFile, line)) {
		str.set(line, "#");
		string fr = str.next(); fr = trim(fr);
		string to = str.next(); to = trim(to);
		string _wet_ = str.next(); _wet_ = trim(_wet_);
		double wet = atof(_wet_.c_str());
		edges.push_back(Edge(fr, to, wet));
	}

	return edges;
}

void print_edges(vector<Edge>& edges) {
	vector<Edge>::iterator it;
	for (it = edges.begin(); it != edges.end(); ++it) {
		cout << it->get_fr() << ", " 
			<< it->get_to() << ", " 
			<< it->get_wet() << endl;
	}
}

map<string, int> make_node_index(vector<Edge>& edges) {
	map<string, int> n2i;
	int index = 0;
	for (int i = 0; i < edges.size(); i++) {
		string fr = edges[i].get_fr();
		string to = edges[i].get_to();
		if (n2i.find(fr) == n2i.end()) {
			n2i.insert(pair<string, int>(fr, index));
			index++;
		}
		if (n2i.find(to) == n2i.end()) {
			n2i.insert(pair<string, int>(to, index));
			index++;
		}
	}
	return n2i;
}

void print_nodes(map<string, int>& nodes) {
	map<string, int>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it)
		cout << it->first << " => " 
			   << it->second << endl;
}

vector<vector<double>> makeGraph(vector<Edge>& edges, map<string, int>& nodes) {
	vector<vector<double>> W;
	int i;
	for (i = 0; i < nodes.size(); i++) {
		vector<double> row(nodes.size(), DBL_MAX);
		W.push_back(row);
	}
	for (i = 0; i < nodes.size(); i++) W[i][i] = 0;
	for (i = 0; i < edges.size(); i++) {
		string fr = edges[i].get_fr();
		string to = edges[i].get_to();
		double wet = edges[i].get_wet();
		W[nodes[fr]][nodes[to]] = wet;
	}
	return W;
}
void print_matrix_dbl(vector<vector<double>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void print_matrix_int(vector<vector<int>>& matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void floyd(map<string, int>& nodes, vector<vector<double>>& W, vector<vector<double>>& D) {
	int i, j, k;
	for (k = 0; k < nodes.size(); k++)
		for (i = 0; i < nodes.size(); i++)
			for (j = 0; j < nodes.size(); j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
}

vector<vector<int>> make_matrix(map<string, int>& nodes) {
	vector<vector<int>> P;
	for (int i = 0; i < nodes.size(); i++) {
		vector<int> row(nodes.size(), 0);
		P.push_back(row);
	}
	return P;
}

void floyd2(map<string, int>& nodes, vector<vector<double>>& W, vector<vector<double>>& D, vector<vector<int>>& P) {
	int i, j, k;
	for (i = 0; i < nodes.size(); i++)
		for (j = 0; j < nodes.size(); j++)
			P[i][j] = 0;
	for (k = 0; k < nodes.size(); k++)
		for (i = 0; i < nodes.size(); i++)
			for (j = 0; j < nodes.size(); j++)
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
}

void print_path(map<string, int>& nodes, vector<vector<int>>& P) {
	string node;
	for (int i = 0; i < nodes.size(); i++)
		for (int j = 0; j < nodes.size(); j++)
			if (i != j) {
				node = find_nodes_key(nodes, i);
				cout << node << " -> ";
				path(nodes, P, i, j);
				node = find_nodes_key(nodes, j);
				cout << node << endl;
			}
}

void path(map<string, int>& nodes, vector<vector<int>>& P, int q, int r) {
	string node;
	if (P[q][r] != 0) {
		path(nodes, P, q, P[q][r]);
		node = find_nodes_key(nodes, P[q][r]);
		cout << node << " -> ";
		path(nodes, P, P[q][r], r);
	}
}

string find_nodes_key(map<string, int>& nodes, int key) {
	map<string, int>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it)
		if (it->second == key)
			return it->first;
}