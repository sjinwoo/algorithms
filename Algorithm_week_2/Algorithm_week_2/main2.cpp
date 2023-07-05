#define _CRT_SECURE_NO_WARINIGS
#include <iostream>
#include <ctime>
#include <vector>

#define NUM_FUNC 2

using namespace std;

int fibo_recursive(int n);
int fibo_iterative(int n);
void print_time(int n, const char* name, int (*func)(int));

// main function
int main() {
	struct {
		const char* name;
		int (*func)(int);
	} fibo[] = {
		{"fibo_recursive", fibo_recursive},
		{"fibo_iterative", fibo_iterative}
	};
	int n = 30;

	for (int i = 0; i < NUM_FUNC; i++)
		print_time(n, fibo[i].name, fibo[i].func);

	return 0;
}

// fibo functions
int fibo_recursive(int n) {
	if (n <= 1) return n;
	else return fibo_recursive(n - 1) + fibo_recursive(n - 2);
}

int fibo_iterative(int n) {
	vector<int> f;
	f.push_back(0);
	f.push_back(1);
	for (int i = 2; i <= n; i++) f.push_back(f[i - 1] + f[i - 2]);
	return f[n];
}

// print function
void print_time(int n, const char* name, int (*func)(int)) {
	clock_t begin = clock();
	int f_value = func(n);
	clock_t end = clock();
	double elapsed_sec = double(end - begin) / CLOCKS_PER_SEC;
	cout << name << "(" << n << ") = " << f_value << " / time = " << elapsed_sec << '\n';
}
