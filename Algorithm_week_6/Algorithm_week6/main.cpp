#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;
#include "trim.h"
#include "Tokenizer.h"

#define INSERT 1
#define SUBST 2
#define DELETE 3

// 선언문
vector<string> read_words(const char* fname);
int opt(string word1, string word2);
vector<vector<int>> make_matrix(int n, int m);
int minimum(int op1, int op2, int op3, int& index);


// main문
int main() {
	const char* fname = "words.txt";
	vector<string> words = read_words(fname);
	/*for (int i = 0; i < words.size(); i++) {
		int j = 0;
		int min_edit_dist = opt(words[i], words[j]);
		for (j; j < words.size(); j++) {
			if (i == j) continue;
			int temp = opt(words[i], words[j]);
			if ((i == 0 && j == 0) && (min_edit_dist > temp)) min_edit_dist = temp;
			
		}
		cout << words[i] << ", " << words[j] << endl;
		cout << endl;
	}*/
	int a = opt("CCGGGTTACCA", "GGAGTTCA");

	return 0;
}


// 함수
vector<string> read_words(const char* fname) {
	vector<string> words;
	string line;
	ifstream infile(fname);

	if (!infile.is_open()) {
		cerr << "Could not open the file - '" << fname << "'" << endl;
		exit(EXIT_FAILURE);
	}
	while (getline(infile, line)) {
		words.push_back(line);
	}
	return words;
}

int opt(string word1, string word2) {
	int n = word1.size() + 1;
	int m = word2.size() + 1;
	word1 = word1 + "$";
	word2 = word2 + "$";
	vector<vector<int>> dist = make_matrix(n, m);
	vector<vector<int>> path = make_matrix(n, m);
	// initialize
	dist[n - 1][m - 1] = 0;
	for (int i = (n - 2); i >= 0; i--) {
		dist[i][m - 1] = dist[i + 1][m - 1] + 2;
		path[i][m - 1] = DELETE;
	}
	for (int j = (m - 2); j >= 0; j--) {
		dist[n - 1][j] = dist[n - 1][j + 1] + 2;
		path[n - 1][j] = INSERT;
	}
	
	// dp
	for (int i = (n - 2); i >= 0; i--) {
		for (int j = (m - 2); j >= 0; j--) {
			int op1 = dist[i][j + 1] + 2;
			int op2 = dist[i + 1][j + 1] + (word1[i] == word2[j] ? 0 : 1);
			int op3 = dist[i + 1][j] + 2;
			int index = 0;
			dist[i][j] = minimum(op1, op2, op3, index);
			path[i][j] = index;
		}
	}

	for (int i = 0; i < dist.size(); i++) {
		for (int j = 0; j < dist[i].size(); j++) cout << setw(2) << path[i][j] << " ";
		cout << endl;
	}

	 // print a pairs of alignment
	int t = 0; int i = 0; int j = 0;
	while(t < (max(n, m) - 1)) {
		if (path[i][j] == INSERT)
			cout << "(" << "-" << ", " << word2[j++] << ")" << endl;
		else if (path[i][j] == SUBST)
			cout << "(" << word1[i++] << ", " << word2[j++] << ")" << endl;
		else
			cout << "(" << word1[i++] << ", " << "-" << ")" << endl;
		t++;
	}
	return dist[0][0];
}

vector<vector<int>> make_matrix(int n, int m) {
	vector<vector<int>> matrix;
	for (int i = 0; i < n; i++) {
		vector<int> row(m, 0);
		matrix.push_back(row);
	}
	return matrix;
}

int minimum(int x, int y, int z, int& index) {
	int smallest = INT_MAX;
	if (x < smallest) {
		smallest = x; index = INSERT;
	}
	if (y < smallest) {
		smallest = y; index = SUBST;
	}
	if (z < smallest) {
		smallest = z; index = DELETE;
	}
	return smallest;
}
