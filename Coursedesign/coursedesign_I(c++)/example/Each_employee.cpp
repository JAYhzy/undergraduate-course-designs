#define _CRT_SECURE_NO_WARNINGS
#include "Each_employee.h"
#include <iostream>
#include <iomanip>
using namespace std;

Technicist::Technicist(string t_name, string t_sex, int t_ID, int t_DpetId)
{
	this->setname(t_name);
	this->setsex(t_sex);
	this->setID(t_ID);
	this->setDeptId(t_DpetId);
	this->salary = 6000;
}
void Technicist::Showinformation()
{
	cout << "员工编号: " << this->getID() << "\t员工姓名:" << setw(8) << left << this->getname()
		<< "\t性别: " << this->getsex() << "\t岗位: " << left << getDeptname() 
		<< "\t月工资: " << this->getsalary() << endl;
}
string Technicist::getDeptname()
{
	return string("技术人员");
}
int Technicist::getsalary()
{
	return salary;
}

Manager::Manager(string m_name, string m_sex, int m_ID, int m_DpetId)
{
	this->setname(m_name);
	this->setsex(m_sex);
	this->setID(m_ID);
	this->setDeptId(m_DpetId);
	this->salary = 10000;
}
void Manager::Showinformation()
{
	cout << "员工编号: " << this->getID() << "\t员工姓名:" << setw(8) << left << this->getname()
		<< "\t性别: " << this->getsex() << "\t岗位: " << left << getDeptname()
		<< "\t月工资: " << this->getsalary() << endl;
}
string Manager::getDeptname()
{
	return string("经理");
}
int Manager::getsalary()
{
	return salary;
}

Salesman::Salesman(string s_name, string s_sex, int s_ID, int s_DpetId)
{
	this->setname(s_name);
	this->setsex(s_sex);
	this->setID(s_ID);
	this->setDeptId(s_DpetId);
	this->salary = 4000;
}
void Salesman::Showinformation()
{
	cout << "员工编号: " << this->getID() << "\t员工姓名:" << setw(8) << left << this->getname()
		<< "\t性别: " << this->getsex() << "\t岗位: " << left << getDeptname()
		<< "\t月工资: " << this->getsalary() << endl;
}
string Salesman::getDeptname()
{
	return string("销售人员");
}
int Salesman::getsalary()
{
	return salary;
}

Sales_Manager::Sales_Manager(string sm_name, string sm_sex, int sm_ID, int sm_DpetId)
{
	this->setname(sm_name);
	this->setsex(sm_sex);
	this->setID(sm_ID);
	this->setDeptId(sm_DpetId);
	this->salary = 8000;
}
void Sales_Manager::Showinformation()
{
	cout << "员工编号: " << this->getID() << "\t员工姓名:" << setw(8) << left << this->getname()
		<< "\t性别: " << this->getsex() << "\t岗位: " << left << getDeptname()
		<< "\t月工资: " << this->getsalary() << endl;
}
string Sales_Manager::getDeptname()
{
	return string("销售经理");
}
int Sales_Manager::getsalary()
{
	return salary;
}