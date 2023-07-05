#ifndef FUNCTIONS_H
#define FUNCTIONS_H

vector<Student> read_data(const char* fname);
void quick_sort(vector<Student>& students, int low, int high);
void my_partition(vector<Student>& students, int low, int high, int& pivot);
void my_quick_sort(vector<Student>& students);

#endif
