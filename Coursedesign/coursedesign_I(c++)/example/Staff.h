#pragma once
#include <string>
using namespace std;

class Staff
{
private:
	string name;
	string sex;
	int ID;//职工编号
	int DeptId;//部门编号
public:
	Staff();
	virtual void Showinformation() = 0;//显示信息
	virtual string getDeptname() = 0;//获取岗位名称
	void setname(string w_name);
	string getname();
	void setsex(string w_sex);
	string getsex();
	void setID(int w_id);
	int getID();
	void setDeptId(int w_deptid);
	int getDeptId();
};