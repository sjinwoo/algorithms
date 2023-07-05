
#ifndef EDGE_H
#define EDGE_H
#include <string>
#include <vector>

using namespace std;

class Edge {
public:
	Edge();									// default constructor 
	Edge(string fr, string to, double wet); // constructor
	string get_fr() const;
	string get_to() const;
	double get_wet() const;
	void set_fr(string fr);
	void set_to(string to);
	void set_wet(double wet);
private:
	string fr;		// source node
	string to;		// destination node
	double wet;		// weight
};

vector<Edge> read_edges(const char* fname);
void print_edges(vector<Edge>& edges);
map<string, int> make_node_index(vector<Edge>& edges);
void print_nodes(map<string, int>& nodes);
vector<vector<double>> makeGraph(vector<Edge>& edges, map<string, int>& nodes);

void print_matrix_dbl(vector<vector<double>>& matrix);
void print_matrix_int(vector<vector<int>>& matrix);
vector<vector<int>> make_matrix(map<string, int>& nodes);

vector<vector<double>> makeGraph(map<string, int>& nodes);
int count_bit(int i);
int travel(map<string, int>& nodes, vector<vector<double>>& W, vector<vector<int>>& P, vector<vector<double>>& D);

void print_path(map<string, int>& nodes, vector<vector<int>>& P);
string find_nodes_key(map<string, int>& nodes, int key);

#endif
