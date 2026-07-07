#include <iostream>
#include "staff.h"
#include"time.h"
#include"allstaff.h"
#include"operate.h"
#include "management.h"
using namespace std;

int main()
{
	int code = 0;
	StaffManager manage;
	while (1)
	{
		//Management::vacate();
		manage.menu();
		cout << "ÇëÊäÈëÄãµÄÖ¸Áî: ";
		cin >> code;

		switch (code)
		{
		case 0:
			manage.ExitSystem();
			break;
		case 1:
			manage.AddStaff();
			break;
		case 2:
			manage.print();
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
			manage.sign_Staff();
			break;
		case 8:
			manage.leave_Staff();
			break;
		default:
			break;
		}
	}
	return 0;
}