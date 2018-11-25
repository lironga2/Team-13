#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Requirements_1_to_4.h"
using namespace std;




typedef struct {
	int id;
	string first_name;
	string last_name;
	int level;
	int phone_number;
}Worker;

void Login();
bool isValid(string user, string pass);
void load_details(string user_name);
void menu(Worker* worker);
void general_worker(Worker* worker);
void shift_manager(Worker* worker);


void Login()
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
	} while ((!flag) && ((exit == 'y') || (exit == 'Y')));
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
	UsersData.close();
}


void load_details(string user_name)
{
	Worker* worker = new Worker;
	string file_user;
	bool flag = false;
	ifstream UsersData;
	UsersData.open("Employee.txt");
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
	menu(worker);
}

void menu(Worker* worker)
{
	int opt;
	switch (worker->level)
	{
	case 1:
	{
		general_worker(worker);
		break;
	}
	case 2:
	{
		shift_manager(worker);
		break;
	}
	case 3:
	{
		//supply_manager(worker);
		break;
	}
	case 4:
	{
		//store_manager(worker);
		break;
	}
	}
}
void general_worker(Worker* worker)
{
	int opt;
	bool flag = false;

	do
	{
		cout << "press 1 to create bill" << endl;
		cout << "press 2 to add club member" << endl;
		cout << "press 3 to check if product in stock" << endl;
		cout << "press 4 to check product price" << endl;
		cout << "press 5 to locate transaction" << endl;
		cout << "press 6 to create your daily sells report" << endl;
		cout << "press 7 to create your daily club members report" << endl;
		cout << "press 0 to back" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			creatBill();
			break;
		}
		case 2:
		{
			//addClubMember();
			break;
		}
		case 3:
		{
			//productInStock();
			break;
		}
		case 4:
		{
			//productPrice();
			break;
		}
		case 5:
		{
			//locateTransaction();
			break;
		}
		case 6:
		{
			//dailySalesReport();
			break;
		}
		case 7:
		{
			//dailyClubMebmer();
			break;
		}
		case 0:
		{
			Login();
			flag = true;
			break;
		}
		}
	} while (!flag);
}
void shift_manager(Worker* worker)
{
	int opt;
	bool flag = false;

	do
	{
		cout << "press 1 to create bill" << endl;
		cout << "press 2 to add club member" << endl;
		cout << "press 3 to check if product in stock" << endl;
		cout << "press 4 to check product price" << endl;
		cout << "press 5 to locate transaction" << endl;
		cout << "press 6 to create your daily sells report" << endl;
		cout << "press 7 to create your daily club members report" << endl;
		cout << "press 0 to back" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			//createBill();
			break;
		}
		case 2:
		{
			//addClubMember();
			break;
		}
		case 3:
		{
			//productInStock();
			break;
		}
		case 4:
		{
			//productPrice();
			break;
		}
		case 5:
		{
			//locateTransaction();
			break;
		}
		case 6:
		{
			//dailySalesReport();
			break;
		}
		case 7:
		{
			//dailyClubMebmer();
			break;
		}
		case 8:
		{
			//returnProduct();
			break;
		}
		case 9:
		{
			//workerBonus();
			break;
		}
		case 10:
		{
			//removeBonus();
			break;
		}
		case 11:
		{
			//saleNewGiftCard();
			break;
		}
		case 0:
		{
			Login();
			flag = true;
			break;
		}
		}
	} while (!flag);

}

