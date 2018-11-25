#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

typedef struct {
	int id;
	string name;
	int level;
	int phone_number;
}Worker;

bool Login()
{
	bool flag = false;
	char exit;
	string user_name;
	string password;
	do
	{
		cout << "Please enter your username" << endl;
		cin >> user_name;
		cout << "Please enter your password" << endl;
		cin >> password;
		if (isValid(user_name, password))
		{
			cout << "You have been connected to user:" << user_name << endl;
			flag = true;
		}
		else
		{
			cout << "User name or password are incorrect" << endl;
			cout << "If you want try again press Y or y to exit press any other key" << endl;
			cin >> exit;
		}
	} while ((!flag) && ((exit != 'y') || (exit != 'Y')));
	if (flag)
	{
		load_details(user_name);
	}
}

bool isValid(string user, string pass)
{
	string file_user;
	string file_pass;
	ifstream UsersData;
	UsersData.open("UserAndPass.txt");
	if (UsersData.is_open())
	{
		while (!UsersData.eof())
		{
			UsersData >> file_user;
			UsersData >> file_pass;
			if ((user.compare(file_user) == 0) && (pass.compare(file_pass) == 0))
			{
				return true;
			}
		}
		return false;
	}
}


Worker load_details(string user_name)
{

}
