#include <string>
#include <vector>
#include "MInfo.h"
using namespace std;

MInfo::MInfo() {}

MInfo::MInfo(string _name_, int _row_, int _col_) {
	name = _name_;
	row = _row_;
	col = _col_;
}

string MInfo::get_name() const {
	return name;
}

int MInfo::get_row() const {
	return row;
}

int MInfo::get_col() const {
	return col;
}

void MInfo::set_name(string _name_) {
	name = _name_;
}

void MInfo::set_row(int _row_) {
	row = _row_;
}

void MInfo::set_col(int _col_) {
	col = _col_;
}



