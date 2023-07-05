#define _CRT_SECURE_NO_WARINIGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#define NUM_FUNC 2

using namespace std;

string read_from_file(const char* fname);
vector<string> split_string(string text);
map<string, int> count_words(vector<string> words);
int linear_search(vector<string> words, string key);
int binary_search(vector<string> words, string key);
void print_time(const char* name, int (*func)(vector<string>, string), vector<string> words, string key);

int main() {
	struct {
		const char* name;
		int (*func)(vector<string>, string);
	} search[] = {
		{"linear_search", linear_search},
		{"binary_search", binary_search}
	};

	string text = read_from_file("news.txt");
	vector<string> words = split_string(text);
	string key = "ÇÑ¹Ýµµ";

	for (int i = 0; i < NUM_FUNC; i++)
		print_time(search[i].name, search[i].func, words, key);

	//map<string, int> freq = count_words(words);
	//map<string, int>::iterator it;
	//for (it = freq.begin(); it != freq.end(); ++it)
	//	cout << it->first << " => " << it->second << endl;
	return 0;
}

string read_from_file(const char* fname) {
	// open file with read mode
	ifstream inFile(fname);
	stringstream strStream;
	strStream << inFile.rdbuf();
	return strStream.str();
}

vector<string> split_string(string text) {
	vector<string> words;
	stringstream sS(text);
	string word;
	while (sS >> word)
		words.push_back(word);
	return words;
}

map<string, int> count_words(vector<string> words) {
	map<string, int> freq;
	for (int i = 0; i < words.size(); i++) {
		freq[words[i]]++;
	}
	return freq;
}

int linear_search(vector<string> words, string key) {
	for (int i = 0; i < words.size(); i++)
		if (words[i] == key) return i;
	return -1;
}

int binary_search(vector<string> words, string key) {
	sort(words.begin(), words.end());

	int low = 0;
	int high = (int)words.size() - 1;
	int pivot;
	while (low <= high) {
		pivot = (low + high) / 2;
		if (words[pivot] == key) return pivot;
		else if (words[pivot] < key) low = pivot + 1;
		else high = pivot - 1;
	}
	return -1;
}

void print_time(const char* name, int (*func)(vector<string>, string), vector<string> words, string key) {
	clock_t begin = clock();
	int f_value = func(words, key);
	clock_t end = clock();
	double elapsed_sec = double(end - begin) / CLOCKS_PER_SEC;
	cout << name << "(" << key<< ") = " << f_value << " / time = " << elapsed_sec << '\n';
}