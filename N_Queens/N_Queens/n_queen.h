#ifndef N_QUEEN_H
#define N_QUEEN_H
#include <string>
#include <vector>
using namespace std;

vector<int> make_list(int n);
void queens(int i, vector<int>& col);
bool promising(int i, vector<int>& col);
void print_list(vector<int>& col);

#endif