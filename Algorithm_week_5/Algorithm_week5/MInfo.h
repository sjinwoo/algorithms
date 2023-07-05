
#ifndef MINFO_H
#define MINFO_H
#include <string>
#include <vector>

using namespace std;

class MInfo {
public:
	MInfo();							  // default constructor 
	MInfo(string name, int row, int col); // constructor
	string get_name() const;
	int get_row() const;
	int get_col() const;
	void set_name(string name);
	void set_row(int row);
	void set_col(int col);
private:
	string name;	
	int row;	
	int col;		
};

#endif
