#pragma once

class Management{
public:
	Management();
	static int vacate();//请假
	int get_Hour();
	void set_Hour(int);
	void set_day1(int);
	void set_day2(int);
	void set_day3(int);
	void set_day4(int);
	double get_day1();
	double get_day2();
	double get_day3(); 
	double get_day4();
	double  get_theday();
	void set_theday(double);
private:
	int hour;
	double shift(double);//时间转换
	double theday;
	double day;
	double day1;//生病没工作天数
	double day2;//生病不工作最多天数
	double day3;//已经带薪休假天数
	double day4;//还可以带薪休假天数
};