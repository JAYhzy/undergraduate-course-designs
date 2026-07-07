#include "operate.h"
#include "allstaff.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "time.h"
#include "management.h"
using namespace std;

StaffManager::StaffManager()
{
	ifstream infile;
	infile.open("staff.txt", ios::in);
	//判断文件打开
	if (!infile.is_open())
	{
		this->number = 0;
		this->staffptr = NULL;
		this->fileisempty = true;
		infile.close();
		return;
	}
	//员工数目
	int num = this->getfileWorkernum();
	this->number = num;
	this->staffptr = new Staff * [this->number];
	//初始化
	this->init_Staff();
	infile.close();
}
//释放空间
StaffManager::~StaffManager()
{
	if (this->staffptr != NULL)
	{
		for (int i = 0; i < this->number; i++)
		{
			if (this->staffptr != NULL)
			{
				delete this->staffptr[i];
			}
		}
		delete[] this->staffptr;
		this->staffptr = NULL;
	}
}
void StaffManager::menu()
{
	cout << "*********************************************" << endl;
	cout << "*          公司员工考勤管理系统               " << endl;
	cout << "*              0.退出系统                 " << endl;
	cout << "*              1.增加员工                 " << endl;
	cout << "*              2.显示信息                 " << endl;
	cout << "*              3.删除员工                 " << endl;
	cout << "*              4.编辑                     " << endl;
	cout << "*              5.查找                     " << endl;
	cout << "*              6.统计                     " << endl;
	cout << "*              7.考勤                     " << endl;
	cout << "*              8.请假                     " << endl;
	cout << endl;
}
void StaffManager::ExitSystem()
{
	cout << "Thanks!" << endl;
	exit(0);
}
void StaffManager::AddStaff()
{
	cout << "请输入想添加的员工的数量: ";

	int addnum = 0;
	cin >> addnum;

	if (addnum > 0)
	{
		int newSize = addnum + number;
		Staff** Newspace = new Staff * [newSize*2];

		if (this->staffptr != NULL)//拷贝旧数据
		{
			for (int i = 0; i < this->number; i++)
			{
				Newspace[i] = this->staffptr[i];
			}
		}
		for (int i = 0; i < addnum; i++)//添加新数据
		{
			int num;
			string name;
			string sex;
			int p;
			cout << "请输入新员工编号: ";
			cin >> num;
			int j = 0;
			while (j < this->number)
			{
				if (this->staffptr == NULL)
				{
					cout << "Error!" << endl;
					exit(0);
				}
				else if (this->staffptr[j]->get_num() == num)
				{//重新循环
					j = 0;
					cout << "编号已存在，请重新输入: ";
					cin >> num;
				}
				else
					j++;
			}
			cout << "请输入员工姓名: ";
			cin >> name;
			cout << "请输入员工性别: ";
			cin >> sex;
			cout << "请选择员工的岗位代号: " << endl;
			cout << "1.technicist" << endl;
			cout << "2.manager" << endl;
			cout << "3.salesman" << endl;
			cout << "4.sales_manager" << endl;
			cin >> p;

			Staff* worker = NULL;
			switch (p)//录入员工的信息并储存
			{
			case 1:
				worker = new Technicist(name, sex, num, 1);
				break;
			case 2:
				worker = new Manager(name, sex, num, 2);
				break;
			case 3:
				worker = new Salesman(name, sex, num, 3);
				break;
			case 4:
				worker = new Sales_Manager(name, sex, num, 4);
			default:
				break;
			}

			Newspace[this->number + i] = worker;
		}
		//释放原有空间
		delete[] this->staffptr;
		//更改新空间指向
		this->staffptr = Newspace;
		//更新职工人数
		this->number = newSize;
		cout << "成功添加"<<endl;
		//保存到文件中
		this->Savefile();
		//更新文件状态不为空
		this->fileisempty = false;
	}
	else
	{
		cout << "失败请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
void StaffManager::Savefile()
{
	ofstream outfile;
	outfile.open("staff.txt", ios::out);

	//写入
	for (int i = 0; i < this->number; i++)
	{
		outfile << this->staffptr[i]->get_num() << ' '
			<< this->staffptr[i]->get_name() << ' '
			<< this->staffptr[i]->get_sex() << ' '
			<< this->staffptr[i]->get_Deptname() << ' '
			<< this->staffptr[i]->get_hour() << ' '
			<< get_day1() << ' '
			<< get_day2() << ' '
			<< get_day3() << ' '
			<< get_day4() << endl
			<< get_hour();
	}
	outfile.close();
}
//计数
int StaffManager::getfileWorkernum()
{
	ifstream infile;
	infile.open("staff.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "打开失败" << endl;
		exit(0);
	}

	int num1 = 0;
	string name;
	string sex;
	int temp = 0;

	int num = 0;
	while (infile >> num1 && infile >> name && infile >> sex && infile >> temp)
	{
		num++;
	}

	return num;
}
//读取出文件的信息
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
	int tep = 0;
	int workernum = 0;

	while (infile >> id && infile >> name && infile >> sex && infile >> tep)
	{
		Staff* worker = NULL;
		if (tep == 1)
		{
			worker = new Technicist(name, sex, id, tep);
		}
		else if (tep == 2)
		{
			worker = new Manager(name, sex, id, tep);
		}
		else if (tep == 3)
		{
			worker = new Salesman(name, sex, id, tep);
		}
		else if (tep == 4)
		{
			worker = new Sales_Manager(name, sex, id, tep);
		}
		this->staffptr[workernum] = worker;
		workernum++;
	}
	infile.close();
}
//输出数据
void StaffManager::print()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		for (int i = 0; i < this->number; i++)
		{
			this->staffptr[i]->Showinformation();
		}
	}
	system("pause");
	system("cls");
}
//查询是否存在
int StaffManager::Staffexist(int id)
{
	for (int i = 0; i < this->number; i++)
	{
		if (this->staffptr[i]->get_num() == id)
		{
			//position
			return i;
			//break;
		}
	}
	return 0;
}
void StaffManager::Delete_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入想删除的员工id: ";
		int num = 0;
		cin >> num;
		int position = this->Staffexist(num);

		if (position != -1)//存在
		{
			//数组数据前移
			for (int i = position; i < this->number; i++)
			{
				this->staffptr[i] = this->staffptr[i + 1];
			}
			this->number--;//更新人员数

			this->Savefile();//把文件数据更新覆盖

			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}
	}
	system("cls");
}
//修改职位
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
			delete this->staffptr[position];

			string newname;
			string newsex;
			int newid = 0;
			int newDeptid = 0;

			cout << "请重新输入该员工编号：";
			cin >> newid;
			int j = 0;
			while (j < this->number)
			{
				if (this->staffptr == NULL)
				{
					cout << "发生错误!" << endl;
					exit(EXIT_FAILURE);
				}
				else if (this->staffptr[j]->get_num() == newid)
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
			this->staffptr[position] = worker;

			//更新保存在文件中
			this->Savefile();
			cout << "修改成功" << endl;
		}
		else
		{
			cout << "修改失败，请检查" << endl;
		}

	}
	system("pause");
	system("cls");
}
//统计
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
		for (int i = 0; i < this->number; i++)
		{
			if (this->staffptr[i]->get_departid() == 1)
			{
				technum++;
			}
			else if (this->staffptr[i]->get_departid() == 2)
			{
				managernum++;
			}
			else if (this->staffptr[i]->get_departid() == 3)
			{
				salesnum++;
			}
			else if (this->staffptr[i]->get_departid() == 4)
			{
				salesmanagernum++;
			}
			if (this->staffptr[i]->get_sex() == "男")
			{
				boynum++;
			}
			if (this->staffptr[i]->get_sex() == "女")
			{
				girlnum++;
			}
		}
		cout << "公司员工总人数：" << this->number << endl;
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
		int q;
		cin >> q;
		int position = this->Staffexist(q);
		if (position != -1)//存在
		{
			this->staffptr[position]->Showinformation();
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void StaffManager::leave_Staff()
{

	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入你的员工编号：";
		int q;
		cin >> q;
		int position = this->Staffexist(q);
		if (position != -1)
		{
			int i = Management::vacate();
			if (i == 1) {
				cout << "你的工资将降低" << endl;
			}
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}
	}
	system("pause");
	system("cls");
}


void StaffManager::sign_Staff()
{
	if (this->fileisempty)
	{
		cout << "文件不存在或数据为空!" << endl;
	}
	else
	{
		cout << "输入你的员工编号：";
		int q;
		cin >> q;
		int position = this->Staffexist(q);
		if (position != -1)
		{
			int hour=Time::infom();
			cout << "今天工作" << hour << "时";
		}
		else
		{
			cout << "未找到该员工!" << endl;
		}
	}
	system("pause");
	system("cls");
}