#define _CRT_SECURE_NO_WARINIGS
#include <iostream>
#include <ctime>

using namespace std;

int fibo_recursive(int n);
int fibo_iterative(int n);

// main function
int main() {
	int n = 30;
	clock_t begin = clock();
	int f_value1 = fibo_recursive(n);
	clock_t end = clock();
	double elapsed_sec = double(end - begin) / CLOCKS_PER_SEC;
	cout << "fib1(" << n << ") = " << f_value1 << " / time = " << elapsed_sec << '\n';

	clock_t start2 = clock();
	int f_value2 = fibo_iterative(30);
	clock_t end2 = clock();
	double elapsed_sec2  = double(end2 - start2) / CLOCKS_PER_SEC;
	cout << "fib2(" << n << ") = " << f_value2 << " / time = " << elapsed_sec2 << '\n';


	//int f_value2 = fibo_iterative(n);
	//cout << "fib2(" << n << ") = " << f_value2 << '\n';

	return 0;
}

// fibo
int fibo_recursive(int n) {
	if (n <= 1) return n;
	else return fibo_recursive(n - 1) + fibo_recursive(n - 2);
}

#define MAX_SIZE 1000
int fibo_iterative(int n) {
	int f[MAX_SIZE];
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i <= n; i++) f[i] = f[i - 1] + f[i - 2];
	return f[n];
}