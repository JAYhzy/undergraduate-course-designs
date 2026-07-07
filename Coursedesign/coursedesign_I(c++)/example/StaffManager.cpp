
#include "StaffManager.h"
#include "Each_employee.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


StaffManager::StaffManager()
{
	ifstream infile;
	infile.open("staff.txt", ios::in);
	//文件不存在
	if (!infile.is_open())//打开失败
	{
		//cout << "文件不存在" << endl;
		this->staffnum = 0;
		this->staffarrptr = NULL;
		this->fileisempty = true;
		infile.close();
		return;
	}
	//文件存在但数据为空
	char ch;
	infile >> ch;//读走一个字符
	if (infile.eof())//为空的话此时指向EOF
	{
		//cout << "文件为空" << endl;
		this->staffnum = 0;
		this->staffarrptr = NULL;
		this->fileisempty = true;
		infile.close();
		return;
	}
	//文件存在且文件中存在数据
	int num = this->getfileWorkernum();
	//cout << "职工人数为:" << num << endl;
	this->staffnum = num;

	this->staffarrptr = new Staff * [this->staffnum];

	this->init_Staff();
	//测试
	//for (int i = 0; i < this->workernum; i++)
	//{
	//	cout << this->staffarrptr[i]->getID() << " "
	//		<< this->staffarrptr[i]->getname() << " "
	//		<< this->staffarrptr[i]->getDeprId() << endl;
	//}

	infile.close();
}
StaffManager::~StaffManager()
{
	if (this->staffarrptr != NULL)
	{
		for (int i = 0; i < this->staffnum; i++)
		{
			if (this->staffarrptr != NULL)
			{
				delete this->staffarrptr[i];
			}
		}
		delete[] this->staffarrptr;
		this->staffarrptr = NULL;
	}
}
void StaffManager::Show_menu()
{
	cout << " ============================================" << endl;
	cout << "‖           公司员工信息管理系统           ‖" << endl;
	cout << "‖               0.退出系统                 ‖" << endl;
	cout << "‖               1.增加员工                 ‖" << endl;
	cout << "‖               2.显示员工                 ‖" << endl;
	cout << "‖               3.删除员工                 ‖" << endl;
	cout << "‖               4.编辑员工                 ‖" << endl;
	cout << "‖               5.查找员工                 ‖" << endl;
	cout << "‖               6.统计员工                 ‖" << endl;
	cout << "‖               7.清空文件                 ‖" << endl;
	cout << " ============================================" << endl;
	cout << endl;
}
void StaffManager::ExitSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}
void StaffManager::AddStaff()
{
	cout << "请输入想添加的员工的数量: ";

	int addnum = 0;
	cin >> addnum;

	if (addnum > 0)
	{
		int newSize = addnum + staffnum;
		Staff** Newspace = new Staff * [newSize];

		if (this->staffarrptr != NULL)//拷贝旧数据
		{
			for (int i = 0; i < this->staffnum; i++)
			{
				Newspace[i] = this->staffarrptr[i];
			}
		}
		for (int i = 0; i < addnum; i++)//添加新数据
		{
			int id;
			string name;
			string sex;
			int Dpetselec;
			cout << "请输入第" << i + 1 << "个新员工编号: ";
			cin >> id;
			int j = 0;
			while(j < this->staffnum)
			{
				if (this->staffarrptr == NULL)
				{
					cout << "发生错误!" << endl;
					exit(EXIT_FAILURE);
				}
				else if (this->staffarrptr[j]->getID() == id)
				{
					j = 0;//循环从头开始
					cout << "编号已存在，请重新输入: ";
					cin >> id;
				}
				else
					j++;
			}
			cout << "请输入第" << i + 1 << "个新员工姓名: ";
			cin >> name;
			cout << "请输入第" << i + 1 << "个新员工性别: ";
			cin >> sex;
			cout << "请选择新员工的岗位: " << endl;
			cout << "1.technicist" << endl;
			cout << "2.manager" << endl;
			cout << "3.salesman" << endl;
			cout << "4.sales_manager" << endl;
			cin >> Dpetselec;

			Staff* worker = NULL;
			switch (Dpetselec)
			{
			case 1:
				worker = new Technicist(name, sex, id, 1);
				break;
			case 2:
				worker = new Manager(name, sex, id, 2);
				break;
			case 3:
				worker = new Salesman(name, sex, id, 3);
				break;
			case 4:
				worker = new Sales_Manager(name, sex, id, 4);
			default:
				system("cls");
				break;
			}
			//保存到数组中
			Newspace[this->staffnum + i] = worker;
		}
		//释放原有空间
		delete[] this->staffarrptr;
		//更改新空间指向
		this->staffarrptr = Newspace;
		//更新职工人数
		this->staffnum = newSize;

		//提示添加成功
		cout << "成功添加" << addnum << "名新员工" << endl;

		//保存到文件中
		this->Savefile();
		//更新文件状态不为空
		this->fileisempty = false;
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");
}
void StaffManager::Savefile()
{
	ofstream outfile;
	outfile.open("staff.txt", ios::out);

	//写进去
	for (int i = 0; i < this->staffnum; i++)
	{
		outfile << this->staffarrptr[i]->getID() << ' '
			<< this->staffarrptr[i]->getname() << ' '
			<< this->staffarrptr[i]->getsex() << ' '
			<< this->staffarrptr[i]->getDeptId() << endl;
	}
	outfile.close();
}
int StaffManager::getfileWorkernum()
{
	ifstream infile;
	infile.open("staff.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "打开失败" << endl;
		exit(EXIT_FAILURE);
	}

	int id = 0;
	string name;
	string sex;
	int Deptid = 0;

	int num = 0;
	while (infile >> id && infile >> name && infile >> sex && infile >> Deptid)
	{
		num++;
	}

	return num;
}
void StaffManager::init_Staff()
{
	ifstream infile;
	infile.open("staff.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	int id = 0;
	string name;
	string sex;
	int Deptid = 0;
	int workernum = 0;

	while (infile >> id && infile >> name && infile >> sex && infile >> Deptid)
	{
		Staff* worker = NULL;
		if (Deptid == 1)
		{
			worker = new Technicist(name, sex, id, Deptid);
		}
		else if (Deptid == 2)
		{
			worker = new Manager(name, sex, id, Deptid);
		}
		else if (Deptid == 3)
		{
			worker = new Salesman(name, sex, id, Deptid);
		}
		else if (Deptid == 4)
		{
			worker = new Sales_Manager(name, sex, id, Deptid);
		}
		this->staffarrptr[workernum] = worker;
		workernum++;
	}
	infile.close();
}
void StaffManager::Show_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->staffnum; i++)
		{
			this->staffarrptr[i]->Showinformation();
		}
	}

	system("pause");
	system("cls");
}
int StaffManager::Staffexist(int id)
{
	for (int i = 0; i < this->staffnum; i++)
	{
		if (this->staffarrptr[i]->getID() == id)
		{
			return i;//存在返回在数组中的位置
			break;
		}
	}
	return -1;//不存在返回-1
}
void StaffManager::Delete_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入想删除的员工ID: ";
		int idd = 0;
		cin >> idd;
		int position = this->Staffexist(idd);

		if (position != -1)//存在
		{
			//数组数据前移
			for (int i = position; i < this->staffnum; i++)
			{
				this->staffarrptr[i] = this->staffarrptr[i + 1];
			}
			this->staffnum--;//更新人员数

			this->Savefile();//把文件数据更新覆盖

			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}
	}

	system("pause");
	system("cls");
}
void StaffManager::Amend_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入你想修改的员工编号：";
		int cid;
		cin >> cid;
		int position = this->Staffexist(cid);
		if (position != -1)
		{
			//先删除
			delete this->staffarrptr[position];

			string newname;
			string newsex;
			int newid = 0;
			int newDeptid = 0;

			cout << "请重新输入该员工编号：";
			cin >> newid;
			int j = 0;
			while (j < this->staffnum)
			{
				if (this->staffarrptr == NULL)
				{
					cout << "发生错误!" << endl;
					exit(EXIT_FAILURE);
				}
				else if (this->staffarrptr[j]->getID() == newid)
				{
					j = 0;//循环从头开始
					cout << "编号已存在，请重新输入: ";
					cin >> newid;
				}
				else
					j++;
			}
			cout << "请重新输入该员工姓名：";
			cin >> newname;
			cout << "请重新输入该员工性别：";
			cin >> newsex;
			cout << "1.technicist" << endl;
			cout << "2.manager" << endl;
			cout << "3.salesman" << endl;
			cout << "4.sales_manager" << endl;
			cout << "请重新输入该员工部门编号：";
			cin >> newDeptid;

			Staff* worker = NULL;
			switch (newDeptid)
			{
			case 1:
				worker = new Technicist(newname, newsex, newid, 1);
				break;
			case 2:
				worker = new Manager(newname, newsex, newid, 2);
				break;
			case 3:
				worker = new Salesman(newname, newsex, newid, 3);
				break;
			case 4:
				worker = new Sales_Manager(newname, newsex, newid, 4);
			default:
				system("cls");
				break;
			}
			this->staffarrptr[position] = worker;

			//更新保存在文件中
			this->Savefile();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "没有该员工！" << endl;
		}

	}

	system("pause");
	system("cls");
}//修改员工职位
void StaffManager::Stati_Staff()
{
	int boynum = 0;
	int girlnum = 0;
	int technum = 0;
	int managernum = 0;
	int salesnum = 0;
	int salesmanagernum = 0;
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->staffnum; i++)
		{
			if (this->staffarrptr[i]->getDeptId() == 1)
			{
				technum++;
			}
			else if (this->staffarrptr[i]->getDeptId() == 2)
			{
				managernum++;
			}
			else if (this->staffarrptr[i]->getDeptId() == 3)
			{
				salesnum++;
			}
			else if (this->staffarrptr[i]->getDeptId() == 4)
			{
				salesmanagernum++;
			}
			if (this->staffarrptr[i]->getsex() == "男")
			{
				boynum++;
			}
			if (this->staffarrptr[i]->getsex() == "女")
			{
				girlnum++;
			}
		}
		cout << "公司员工总人数：" << this->staffnum << endl;
		cout << "技术人员人数：" << technum << endl;
		cout << "经理人数：" << managernum << endl;
		cout << "销售人员人数：" << salesnum << endl;
		cout << "销售经理人数：" << salesmanagernum << endl;
		cout << "男生人数：" << boynum << "\t" << "女生人数：" << girlnum << endl;
	}

	system("pause");
	system("cls");
}
void StaffManager::Find_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入你想查找信息的员工编号：";
		int cid;
		cin >> cid;
		int position = this->Staffexist(cid);
		if (position != -1)//存在
		{
			this->staffarrptr[position]->Showinformation();
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}

	}

	system("pause");
	system("cls");
}
void StaffManager::Clean_file()
{
	cout << "确认清空文件？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回菜单" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream outfile;
		outfile.open("staff.txt", ios::trunc);
		outfile.close();

		if (this->staffarrptr != NULL)
		{
			for (int i = 0; i < this->staffnum; i++)
			{
				if (this->staffarrptr[i] != NULL)
				{
					delete this->staffarrptr[i];
				}

			}
			this->staffnum = 0;
			delete[] this->staffarrptr;
			this->staffarrptr = NULL;
			this->fileisempty = true;
		}
		cout << "清除成功" << endl;
		system("pause");
		system("cls");

	}
	else
	{
		system("cls");
	}


}//清空文件
