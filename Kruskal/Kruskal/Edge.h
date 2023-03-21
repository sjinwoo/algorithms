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
	bool compare(const Edge& e1, const Edge& e2);
private:
	string fr;		// source node
	string to;		// destination node
	double wet;		// weight
};

vector<Edge> read_edges(const char* fname);
map<string, int> make_node_index(vector<Edge>& edges);
void print_edges(vector<Edge>& edges);
void print_nodes(map<string, int>& nodes);

int find(int i, int U[]);
void merge(int p, int q, int U[]);
void initial(int n, int U[]);
void kruskal(int n, int m, map<string, int> nodes, vector<Edge>& E, vector<Edge>& F, int U[]);

#endif
