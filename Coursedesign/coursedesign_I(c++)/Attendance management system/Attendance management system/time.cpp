#include <iostream>
#include "time.h"

using namespace std;

Time::Time() {
    hour1 = 0;
    minute1 = 0;
    second1 = 0;
    hour2 = 0;
    minute2 = 0;
    second2 = 0;
}

int Time::get_reachHour() {
    return hour1;
}
int Time::get_reachMinute() {
    return minute1;
}
int Time::get_reachSecond() {
    return second1;
}
int Time::get_leaveHour() {
    return hour2;
}
int Time::get_leaveMinute() {
    return minute2;
}
int Time::get_leaveSecond() {
    return second2;
}
void Time::set_reachHour(int Hour) {
    hour1 = Hour;
}
void Time::set_reachMinute(int Minute) {
    minute1 = Minute;
}
void Time::set_reachSecond(int Second) {
    second1 = Second;
}
void Time::set_leaveHour(int Hour) {
    hour2 = Hour;
}
void Time::set_leaveMinute(int Minute) {
    minute2 = Minute;
}
void Time::set_leaveSecond(int Second) {
    second2 = Second;
}

int Time::infom() {
    //员工打卡
    Time time;
    int timeIn = 0;
    cout << "到达时间(依次录入时,分,秒):" << endl;
    cout << "到达整点" << endl;
    cin >> timeIn;//输入参数
    if (timeIn >= 0 && timeIn < 24) {
        time.set_reachHour(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    cout << "到达分钟" << endl;
    cin >> timeIn;
    if (timeIn >= 0 && timeIn < 60) {
        time.set_reachMinute(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    cout << "到达秒数" << endl;
   cin >> timeIn;
    if (timeIn >= 0 && timeIn < 60) {
        time.set_reachSecond(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }

    cout << "离开时间(依次录入时,分,秒):" << endl;
    cout << "离开整点" << endl;
    cin >> timeIn;
    if (timeIn >= 0 && timeIn < 24) {
        time.set_leaveHour(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    cout << "离开分钟" << endl;
    cin >> timeIn;
    if (timeIn >= 0 && timeIn < 60) {
        time.set_leaveMinute(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    cout << "离开秒数" << endl;
    cin >> timeIn;
    if (timeIn >= 0 && timeIn < 60) {
        time.set_leaveSecond(timeIn);
    }
    else {
        cout << "请正确输入时间" << endl;
        return 0;
    }
    int hour = time.get_leaveHour() - time.get_reachHour();
   // cout << "今天工作" << hour << "时";
    return hour;
}
int Time::get_hour() {
    Time time;
    int hour =time.get_leaveHour() - time.get_reachHour()  ;
    return hour;
}

