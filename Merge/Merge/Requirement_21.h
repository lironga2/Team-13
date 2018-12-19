#pragma once
#include "Requirements_41_to_42.h"
void changeAccess()
{
	Worker* worker = new Worker;
	string file_user;
	bool flag = false;
	ifstream UsersData;
	UsersData.open("Employee.txt");
	//load details of employee that connect to the system
	if (UsersData.is_open())
	{
		while (!UsersData.eof() && (!flag))
		{
			UsersData >> file_user;
			if (user_name.compare(file_user) == 0)
			{
				UsersData >> worker->id;
				UsersData >> worker->first_name;
				UsersData >> worker->last_name;
				UsersData >> worker->level;
				UsersData >> worker->phone_number;
				flag = true;
			}
		}
	}
	UsersData.close();
}