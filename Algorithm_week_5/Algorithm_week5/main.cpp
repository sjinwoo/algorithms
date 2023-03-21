#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "MInfo.h"
#include "trim.h"
#include "Tokenizer.h"
using namespace std;

vector<MInfo> read_matrix_info(string name);
void print_matrix_info(vector<MInfo>& M);
vector<int> make_dimensions(vector<MInfo>& M);
vector<vector<int>> make_matrix(vector<MInfo>& M);
void minmulti(vector<int>& d, vector<vector<int>>& M, vector<vector<int>>& P);
void order(int i, int j, vector<vector<int>>& P, vector<MInfo>& mats);

// main
int main() {
	const string fName = "matrix.txt";
	vector<MInfo> mats = read_matrix_info(fName);
	print_matrix_info(mats);

	vector<int> d = make_dimensions(mats);
	vector<vector<int>> M = make_matrix(mats);
	vector<vector<int>> P = make_matrix(mats);

	 minmulti(d, M, P);
	 order(1, d.size() - 1, P, mats);
	cout << endl;

	return 0;
}

vector<MInfo> read_matrix_info(string fName) {
	vector<MInfo> mats;
	ifstream fin(fName.c_str());
	if (fin.fail()) {
		cerr << "Can't open " << fName << endl;
		return mats;
	}
	string line;
	string name;
	int row, col;
	while (getline(fin, line)) {
		Tokenizer tokens(line, " ");
		string tmp = tokens.next(); name = trim(tmp);
		tmp = tokens.next(); row = atoi(tmp.c_str());
		tmp = tokens.next(); col = atoi(tmp.c_str());
		mats.push_back(MInfo(name, row, col));
	}
	return mats;
}

void print_matrix_info(vector<MInfo>& M) {
	for (int i = 0; i < M.size(); i++)
		cout << i << " : "
		<< M[i].get_name() << " : "
		<< M[i].get_row() << " : "
		<< M[i].get_col() << endl;
}

vector<int> make_dimensions(vector<MInfo>& M) {
	vector<int> d;
	d.push_back(M[0].get_row());
	for (int i = 0; i < M.size(); i++)
		d.push_back(M[i].get_col());
	return d;
}

vector<vector<int>> make_matrix(vector<MInfo>& M) {
	// size + 1 ø° ¡÷¿«.
	vector<vector<int>> matrix;
	for (int i = 0; i <= M.size(); i++) {
		vector<int> row(M.size() + 1, 0);
		matrix.push_back(row);
	}
	return matrix;
}

void minmulti(vector<int>& d, vector<vector<int>>& M, vector<vector<int>>& P) {
	int i, j, diag;
	int n = (int)M[0].size() - 1;
	for (i = 1; i <= n; i++)
		M[i][i] = 0;
	for (diag = 1; diag <= n - 1; diag++)
		for (i = 1; i <= n - diag; i++) {
			j = i + diag;
			for (int k = i; k <= j - 1; k++) {
				int tmp = (M[i][k] + M[k + 1][j] + (d[i - 1] * d[k] * d[j]));
				if ((k == i) || (M[i][j] > tmp)) {
					M[i][j] = tmp;
					P[i][j] = k;
				}
			}
		}
}

void order(int i, int j, vector<vector<int>>& P, vector<MInfo>& mats) {
	if (i == j) cout << "\'" << mats[i - 1].get_name() << "\'";
	else {
		cout << "(";
		order(i, P[i][j], P, mats);
		order(P[i][j] + 1, j, P, mats);
		cout << ")";
	}
}
