
#include <string>
#include "Student.h"

using namespace std;

Student::Student() {}

Student::Student(string _name_, string _telno_){
	name = _name_;
	telno = _telno_;
}

string Student::get_name() const {
	return name;
}

string Student::get_telno() const{
	return telno;
}

void Student::set_name(string _name_) {
	name = _name_;
}

void Student::set_telno(string _telno_) {
	telno = _telno_;
}


bool operator<(const Student& left, const Student& right) {
	return left.get_name() < right.get_name();
}
