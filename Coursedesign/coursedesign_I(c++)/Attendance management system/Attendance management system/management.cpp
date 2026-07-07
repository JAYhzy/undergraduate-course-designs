#include <iostream>
#include"management.h"
using namespace std;
Management::Management() {
	 day1 = 0;
	 day2 = 5;
	 day3 = 0;
	 day4 = 5;
	 hour = 0;
     theday = 0;
}

int Management::get_Hour() {
    return hour;
}
void Management::set_Hour(int Hour) {
    hour = Hour;
}

double Management::get_day1() {
    return day1;
}
double Management::get_day2() {
    return day2;
}
double Management::get_day3() {
    return day3;
}
double Management::get_day4() {
    return day4;
}

void Management::set_day1(int day) {
    day1 = day;
}
void Management::set_day2(int day) {
    day2 = day;
}
void Management::set_day3(int day) {
    day3 = day;
}
void Management::set_day4(int day) {
    day4= day;
}
double Management:: get_theday() {
    return theday;
}
void Management::set_theday(double theday1) {
    theday = theday1;
}

double Management::shift(double hour) {
    while (hour > 4) {
        day += 0.5;
        hour -= 4;
    }
    return day;
}

int Management::vacate() {
    int t1=0, t2=0, time;
    Management example;
    cout << "请选择请假类型:" << endl;
    cout << "1病假\t";
    cout << "2事假" << endl;
    cin >> t1;
    if (t1 == 2) {
        cout << "请选择是否带薪休假:" << endl;
        cout << "1带薪\t";
        cout << "2不带薪" << endl;
        cin >> t2;
    }
    cout << "请输入休假时长:" << endl;
    cout << "小时:" << endl;
    cin >> time;//输入参数
    if (time >= 0) {
        example.set_Hour(time);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    double theday = example.shift(example.get_Hour());
    //不同情况的请假
    if (t1 == 1) {
        if (theday <= 2) {
            example.set_day1(example.get_day1() + theday);
            example.set_day2(example.get_day2() - theday);
            example.set_day3(example.get_day3() + theday);
            example.set_day4(example.get_day4() - theday);
            cout << "请假成功" << endl;
            system("pause");
            system("cls");
            return 0;
        }
        else {
            cout << "请假时间太长不允许" << endl;
            return 0;
        }
        cout << "请假成功" << endl;
        system("pause");
        system("cls");
    }
    else if (t2 == 1) {
        if (theday <= 3) {
            example.set_day3(example.get_day3() + theday);
            example.set_day4(example.get_day4() - theday);
            cout << "请假成功" << endl;
            system("pause");
            system("cls");
            return 0;
        }
        else {
            cout << "请假时间太长不允许" << endl;
            return 0;
        }
        cout << "请假成功" << endl;
        system("pause");
        system("cls");
    }
    else {
        if (theday <= 3) {
            example.set_day3(example.get_day3() + theday);
            example.set_day4(example.get_day4() - theday);
            cout << "请假成功" << endl;
            system("pause");
            system("cls");
            return 1;
        }
        else {
            cout << "请假时间太长不允许" << endl;
            return 0;
        }
        cout << "请假成功" << endl;
        system("pause");
        system("cls");
    }
}