#pragma once
#include "Staff.h"

class Technicist : public Staff
{
private:
	int salary;
public:
	Technicist(string t_name, string t_sex, int t_ID, int t_DpetId);
	virtual void Showinformation();
	virtual string getDeptname();
	int getsalary();
};

class Manager : public Staff
{
private:
	int salary;
public:
	Manager(string m_name, string m_sex, int m_ID, int m_DpetId);
	virtual void Showinformation();
	virtual string getDeptname();
	int getsalary();
};

class Salesman :public Staff
{
private:
	int salary;
public:
	Salesman(string s_name, string s_sex, int s_ID, int s_DpetId);
	virtual void Showinformation();
	virtual string getDeptname();
	int getsalary();
};

class Sales_Manager :public Staff
{
private:
	int salary;
public:
	Sales_Manager(string sm_name, string sm_sex, int sm_ID, int sm_DpetId);
	virtual void Showinformation();
	virtual string getDeptname();
	int getsalary();
};