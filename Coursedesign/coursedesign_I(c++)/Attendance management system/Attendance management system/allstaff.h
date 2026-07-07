#pragma once
#include "Staff.h"
//各种职工
class Technicist : public Staff,Management, Time
{
private:
	double salary;
public:
	Technicist(string name1, string sex1, int num1, int dpepartment1);
	virtual void Showinformation();
	virtual string get_Deptname();
	virtual double get_salary();
};

class Manager : public Staff, Management, Time
{
private:
	double salary;
public:
	Manager(string name1, string sex1, int num1, int dpepartment1);
	virtual void Showinformation();
	virtual string get_Deptname();
	virtual double get_salary();
};

class Salesman :public Staff, Management, Time
{
private:
	double salary;
public:
	Salesman(string name1, string sex1, int num1, int dpepartment1);
	virtual void Showinformation();
	virtual string get_Deptname();
	virtual double get_salary();
};

class Sales_Manager :public Staff, Management, Time
{
private:
	double salary;
public:
	Sales_Manager(string name1, string sex1, int num1, int dpepartment1);
	virtual void Showinformation();
	virtual string get_Deptname();
	virtual double get_salary();
};