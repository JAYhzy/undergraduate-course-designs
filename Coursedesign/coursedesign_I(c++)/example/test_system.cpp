#define _CRT_SECURE_NO_WARNINGS
#include "StaffManager.h"
#include <iostream>
using namespace std;
/*
程序名称：公司员工信息管理系统
作者：12119370120 王钇欢
时间：2022.6.18
版本：反正没有下一个版本的版本
*/


int main()
{
	StaffManager manage;

	int choice = 0;

	while (1)
	{
		manage.Show_menu();
		cout << "请输入你的选择: ";
		cin >> choice;

		switch (choice)
		{
		case 0:
			manage.ExitSystem();//exit;
			break;
		case 1:
			manage.AddStaff();
			break;
		case 2:
			manage.Show_Staff();
			break;
		case 3:
			manage.Delete_Staff();
			break;
		case 4:
			manage.Amend_Staff();
			break;
		case 5:
			manage.Find_Staff();
			break;
		case 6:
			manage.Stati_Staff();
			break;
		case 7:
			manage.Clean_file();
			break;
		default:
			system("cls");
			break;
		}

	}


	system("pause");

	return 0;
}