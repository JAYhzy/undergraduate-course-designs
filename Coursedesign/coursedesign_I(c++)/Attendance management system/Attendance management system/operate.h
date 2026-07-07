#pragma once
#include "Staff.h"
#include "management.h"
#include "time.h"
class StaffManager: public Management,Time
{
public:
	StaffManager();
	~StaffManager();
	void menu();//菜单
	void ExitSystem();//退出
	void AddStaff();//添加
	void print();//打印信息
	void Stati_Staff();//统计
	int Staffexist(int id);//查询是否存在
	void Delete_Staff();//删除
	void Amend_Staff();//修改
	void Find_Staff();//寻找
	void sign_Staff();//考勤
	void leave_Staff();//请假
	void Savefile();//保存

	bool fileisempty;//文件是否有内容

	//统计文件中的人数
	int getfileWorkernum();
	//初始化
	void init_Staff();

	int number;//统计人数
	Staff** staffptr;
};
