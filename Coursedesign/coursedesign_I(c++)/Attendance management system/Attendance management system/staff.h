#pragma once
#include <string>
#include  "time.h"
#include "Management.h"
using namespace std;
class Staff :public Time, Management
{
public:
	//信息建立和获取
	Staff();
	void set_stuff(int, string, string, string, string,double);
	void set_num(int);
	void set_name(string);
	void set_sex(string);
	void set_Departid(int);
	void set_level(string);
	bool set_salary(double);

	int get_num();
	string get_name();
	string get_sex();
	virtual string get_Deptname();
	virtual void Showinformation()=0;
	int get_departid();
	string get_level();
	virtual double get_salary();

	//void add();
	//void query();
	//virtual void print();
	//void edit();
	//void delet();
	//void statistical();
	//void save();
	//void read();
private:
	int num;
	string name;
	string sex;
	string departname;
	int departid;
	string level;
	double salary;
};