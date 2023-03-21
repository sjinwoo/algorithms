#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Edge.h"
#include "trim.h"
#include "Tokenizer.h"

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
bool compareF(const Edge& e1, const Edge& e2) {
	return e1.get_wet() < e2.get_wet();
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
	// Á¤·Ä
	sort(edges.begin(), edges.end(), compareF);
	return edges;
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
void print_edges(vector<Edge>& edges) {
	vector<Edge>::iterator it;
	for (it = edges.begin(); it != edges.end(); ++it) {
		cout << it->get_fr() << ", "
			<< it->get_to() << ", "
			<< it->get_wet() << endl;
	}
}

void kruskal(int n, int m, map<string, int> nodes, vector<Edge>& E, vector<Edge>& F, int U[]) {
	int i, j;
	int p, q;
	Edge e;
	initial(n, U);
	int count = 0;
	for (int k = 0; k <= E.size(); k++) {
		e = E[k];
		i = nodes[e.get_fr()];
		j = nodes[e.get_to()];
		p = find(i, U);
		q = find(j, U);
		if (p != q) {
			merge(p, q, U);
			F.push_back(e);
			count++;
		}
		if (count == n - 1) break;
	}
}
int find(int i, int U[]) {
	int j = i;
	while (U[j] != j) j = U[j];
	return j;
}
void merge(int p, int q, int U[]) {
	if (p < q) U[q] = p;
	else U[p] = q;
}
void initial(int n, int U[]) {
	for (int i = 0; i <= n; i++)U[i] = i;
}