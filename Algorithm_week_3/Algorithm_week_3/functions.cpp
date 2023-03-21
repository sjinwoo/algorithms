#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stdlib.h>

#include "Student.h"
#include "Tokenizer.h"
#include "Functions.h"

// function
vector<Student> read_data(const char* fname) {
	vector<Student> students;
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
		string name = str.next();
		string telno = str.next();
		students.push_back(Student(name, telno));
	}

	return students;
}

void my_quick_sort(vector<Student>& students) {
	int low = 0;
	int high = (int)students.size() - 1;
	quick_sort(students, low, high);
}

void quick_sort(vector<Student>& students, int low, int high) {
	int pivot;
	if (high <= low) return;
	my_partition(students, low, high, pivot);
	quick_sort(students, low, pivot - 1);
	quick_sort(students, pivot + 1, high);
}

void my_partition(vector<Student>& students, int low, int high, int& pivot) {
	int i, j;
	Student pivot_item = students[low];
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (students[i] < pivot_item) {
			j++;
			swap(students[i], students[j]);
		}
	}
	pivot = j;
	swap(students[pivot], students[low]);
}
