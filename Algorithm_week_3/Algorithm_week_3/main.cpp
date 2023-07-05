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

using namespace std;

// main
int main() {
	const char* fname = "data.txt";
	vector<Student> students = read_data(fname);
	vector<Student>::iterator it = students.begin();
	for (it; it != students.end(); ++it) {
		cout << it->get_name() << " " << it->get_telno() << endl;
	}
	
	my_quick_sort(students);
	for (it = students.begin(); it != students.end(); ++it) {
		cout << it ->get_name() << " " << it->get_telno() << endl;
	}
	return 0;
}