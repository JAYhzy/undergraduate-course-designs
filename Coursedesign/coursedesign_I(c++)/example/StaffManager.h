#pragma once
#include "Staff.h"
class StaffManager
{
public:
	StaffManager();
	~StaffManager();
	void Show_menu();//菜单
	void ExitSystem();//退出
	void AddStaff();//添加
	void Show_Staff();//显示
	void Stati_Staff();//统计
	int Staffexist(int id);//判断员工是否存在 并返回在数组中位置
	void Delete_Staff();//删除
	void Amend_Staff();//修改员工职位
	void Find_Staff();//查找员工
	//保存到文件
	void Savefile();
	void Clean_file();//清空文件

	//判断文件是否为空
	bool fileisempty;

	//若文件存在且里面有数据，则统计文件中的人数
	int getfileWorkernum();

	//文件存在人 那么应该把文件里面的数据初始化到当前程序中
	void init_Staff();

	int staffnum;//统计人数
	Staff** staffarrptr;
};