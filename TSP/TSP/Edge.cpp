#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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
vector<vector<double>> makeGraph(map<string, int>& nodes) {
	vector<vector<double>> D;
	int i;
	for (i = 0; i < nodes.size(); i++) {
		vector<double> row(pow(2, nodes.size() - 1), 0);
		D.push_back(row);
	}
	return D;
}
vector<vector<int>> make_matrix(map<string, int>& nodes) {
	vector<vector<int>> P;
	for (int i = 0; i < nodes.size(); i++) {
		vector<int> row(pow(2, nodes.size() - 1), 0);
		P.push_back(row);
	}
	return P;
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

// 1의 개수
int count_bit(int i) {
	int count = 0;
	while (i != 0) {
		if (i & 1) ++count;
		i = i >> 1;
	}
	return count;
}

// nodes : Vi => i - 1  /  W : adj_mat  /  P : path_mat
int travel(map<string, int>& nodes, vector<vector<double>>& W, vector<vector<int>>& P, vector<vector<double>>& D) {
	// initialize
	for (int i = 1; i < nodes.size(); i++)
		D[i][0] = W[i][0];
	// DP
	int temp , min;
	for (int k = 1; k <= nodes.size() - 2; k++) {
		// v1 을 포함하지 않는 V의 부분 집합 A
		for (int A = 0; A < pow(2, (nodes.size() - 1)); A++) {
			// A가 k를 포함하지 않으면 다음 loop로
			if (count_bit(A) != k) continue;
			// i = 0이 아니고
			for (int i = 1; i < nodes.size(); i++) {
				// vi가 A에 없다면
				if ((A & (1 << (i - 1))) == 0) {
					// A의 부분 집합
					min = 10000;
					for (int j = 1; j < nodes.size(); j++) {
						if ((A & (1 << (j - 1))) != 0) {
							temp = W[i][j] + D[j][A - (1 << (j - 1))];
							if (min >= temp) {
								min = temp;
								D[i][A] = min;
								P[i][A] = j;
							}
						}
					}
				}
			}
		}
	}
	int result = INT_MAX;
	for (int j = 1; j < nodes.size(); j++) {
		int temp = W[0][j] + D[j][(D[0].size() - 1) - (1 << (j - 1))];
		if (result > temp) {
			result = temp;
			D[0][D[0].size() - 1] = result;
			P[0][D[0].size() - 1] = j;
		}
	}
	return D[0][D[0].size() - 1];
}

void print_path(map<string, int>& nodes, vector<vector<int>>& P) {
	// v1
	string node;
	node = find_nodes_key(nodes, 0);
	cout << node << " ";
	// 이후 경로
	int size = P[0].size() - 1;
	int index = P[0][size];
	int temp = 1;
	while (temp < nodes.size()) {
		node = find_nodes_key(nodes, index);
		cout << node << " ";
		size = size ^ (1 << (index - 1));
		index = P[index][size];
		temp++;
	}
}

string find_nodes_key(map<string, int>& nodes, int key) {
	map<string, int>::iterator it;
	for (it = nodes.begin(); it != nodes.end(); ++it)
		if (it->second == key)
			return it->first;
}

//// 부분 집합
//map<int, vector<int>> make_subset(int index) {
//	map<int, vector<int>> subsets;
//	subsets.insert(pair<int, vector<int>>(index++, { 2 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 3 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 4 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 3 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 4 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 3, 4 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 3, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 4, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 3, 4 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 3, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 4, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 3, 4, 5 }));
//	subsets.insert(pair<int, vector<int>>(index++, { 2, 3, 4, 5 }));
//	return subsets;
//}
//// 순열
//vector<int> make_permutation_table() {
//	vector<int> table = { 3, 4, 5 };
//	vector<int> res;
//	vector<int>::iterator it;
//	sort(table.begin(), table.end());
//	do {
//		for (it = table.begin(); it != table.end(); it++)
//			res.push_back(*it);
//	} while (next_permutation(table.begin(), table.end()));
//	
//	return res;
//}