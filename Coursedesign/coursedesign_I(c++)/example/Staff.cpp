#define _CRT_SECURE_NO_WARNINGS
#include "Staff.h"

Staff::Staff()
{
	ID = 0;
	DeptId = 0;
}
void Staff::setname(string w_name)
{
	name = w_name;
}
string Staff::getname()
{
	return name;
}
void Staff::setsex(string w_sex)
{
	sex = w_sex;
}
string Staff::getsex()
{
	return sex;
}
void Staff::setID(int w_id)
{
	ID = w_id;
}
int Staff::getID()
{
	return ID;
}
void Staff::setDeptId(int w_deptid)
{
	DeptId = w_deptid;
}
int Staff::getDeptId()
{
	return DeptId;
}