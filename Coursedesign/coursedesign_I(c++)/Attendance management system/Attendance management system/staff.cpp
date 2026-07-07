#include "staff.h"
#include "iostream"
#include  "time.h"
#include <iomanip>
Staff::Staff() {
	num = 0;
	name = "0";
	sex = "0";
	departname = "0";
	level = "0";
	salary = 5000;
}
string Staff::get_Deptname() {
	return departname;
}
//void Staff::Showinformation() {
//
//}

void Staff::set_num(int num1) {
	num = num1;
}
void Staff::set_name(string name1) {
	name = name1;
}
void Staff::set_sex(string sex1) {
	sex = sex1;
}
void Staff::set_Departid(int department1) {
	departid = department1;
}
void Staff::set_level(string level1) {
	level = level1;
}
bool Staff::set_salary(double salary1) {
	if (salary1 > 0) {
		salary = salary1;
		return true;
	}
	else return false;
}

int Staff::get_num() {
	return this->num;
}
string Staff::get_name() {
	return this->name;
}
string Staff::get_sex() {
	return this->sex;
}
int Staff::get_departid() {
	return this->departid;
}
string Staff::get_level() {
	return this->level;
}
double Staff::get_salary() {
	return this->salary;
}

void Staff::set_stuff(int num1, string name1, string sex1, string department1, string level1, double salary1) {
	num = num1;
	name= name1;
	sex = sex1;
	departname = department1;
	level = level1;
	salary = salary1;
}