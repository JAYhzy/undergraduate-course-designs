#pragma once

class Time {
public:
	Time();
	void set_reachHour(int);
	void set_reachMinute(int);
	void set_reachSecond(int);
	void set_leaveHour(int);
	void set_leaveMinute(int);
	void set_leaveSecond(int);
	static int infom();//¿¼ÇÚ

	int get_reachHour();
	int get_reachMinute();
	int get_reachSecond();
	int get_leaveHour();
	int get_leaveMinute();
	int get_leaveSecond();
	int get_hour();
private:
	int hour1;
	int minute1;
	int second1;
	int hour2;
	int minute2;
	int second2;
};