#include "allstaff.h"
#include <iostream>
#include <iomanip>
using namespace std;
//各种员工类
Technicist::Technicist(string name1, string sex1, int num1, int dpepartment1)
{
	this->set_name(name1);
	this->set_sex(sex1);
	this->set_num(num1);
	this->set_Departid(dpepartment1);
	this->salary = 10000;
}
void Technicist::Showinformation()
{
	cout << "员工编号: " << this->get_num() << "\t姓名:" << setw(8) << left << this->get_name()
		<< "\t性别: " << this->get_sex() << "\t岗位: " << left << get_Deptname() << endl
		<< "\t工资: " << this->get_salary() << endl
		<< "考勤情况: " << this->Time::get_hour() << endl << "\t请假情况:" << endl
		<< "1生病没工作天数:" << left << this->Management::get_day1() << endl
		<< "2生病不工作最多天数:" << left << this->Management::get_day2() << endl
		<< "3已经带薪休假天数:" << left << this->Management::get_day3() << endl
		<< "4还可以带薪休假天数:" << left << this->Management::get_day4() << endl;
}
string Technicist::get_Deptname()
{
	return string("技术人员");
}
double Technicist::get_salary()
{
	return salary;
}

Manager::Manager(string name1, string sex1, int num1, int dpepartment1)
{
	this->set_name(name1);
	this->set_sex(sex1);
	this->set_num(num1);
	this->set_Departid(dpepartment1);
	this->salary = 8000;
}
void Manager::Showinformation()
{
	cout << "员工编号: " << this->get_num() << "\t姓名:" << setw(8) << left << this->get_name()
		<< "\t性别: " << this->get_sex() << "\t岗位: " << left << get_Deptname() << endl
		<< "\t工资: " << this->get_salary() << endl
		<< "考勤情况: " << this->Time::get_hour() << endl << "\t请假情况:" << endl
		<< "1生病没工作天数:" << left << this->Management::get_day1() << endl
		<< "2生病不工作最多天数:" << left << this->Management::get_day2() << endl
		<< "3已经带薪休假天数:" << left << this->Management::get_day3() << endl
		<< "4还可以带薪休假天数:" << left << this->Management::get_day4() << endl;
}
string Manager::get_Deptname()
{
	return string("经理");
}
double Manager::get_salary()
{
	return salary;
}

Salesman::Salesman(string name1, string sex1, int num1, int dpepartment1)
{
	this->set_name(name1);
	this->set_sex(sex1);
	this->set_num(num1);
	this->set_Departid(dpepartment1);
	this->salary = 5000;
}
void Salesman::Showinformation()
{
	cout << "员工编号: " << this->get_num() << "\t姓名:" << setw(8) << left << this->get_name()
		<< "\t性别: " << this->get_sex() << "\t岗位: " << left << get_Deptname() << endl
		<< "\t工资: " << this->get_salary() << endl
		<< "考勤情况: " << this->Time::get_hour() << endl << "\t请假情况:" << endl
		<< "1生病没工作天数:" << left << this->Management::get_day1() << endl
		<< "2生病不工作最多天数:" << left << this->Management::get_day2() << endl
		<< "3已经带薪休假天数:" << left << this->Management::get_day3() << endl
		<< "4还可以带薪休假天数:" << left << this->Management::get_day4() << endl;
}
string Salesman::get_Deptname()
{
	return string("销售人员");
}
double Salesman::get_salary()
{
	return salary;
}

Sales_Manager::Sales_Manager(string name1, string sex1, int num1, int dpepartment1)
{
	this->set_name(name1);
	this->set_sex(sex1);
	this->set_num(num1);
	this->set_Departid(dpepartment1);
	this->salary = 8000;
}
void Sales_Manager::Showinformation()
{
	cout << "员工编号: " << this->get_num() << "\t姓名:" << setw(8) << left << this->get_name()
		<< "\t性别: " << this->get_sex() << "\t岗位: " << left << get_Deptname() << endl
		<< "\t工资: " << this->get_salary() << endl
		<< "考勤情况: " << this->Time::get_hour() << endl << "\t请假情况:" << endl
		<< "1生病没工作天数:" << left << this->Management::get_day1() << endl
		<< "2生病不工作最多天数:" << left << this->Management::get_day2() << endl
		<< "3已经带薪休假天数:" << left << this->Management::get_day3() << endl
		<< "4还可以带薪休假天数:" << left << this->Management::get_day4() << endl;
}
string Sales_Manager::get_Deptname()
{
	return string("销售经理");
}
double Sales_Manager::get_salary()
{
	return salary;
}