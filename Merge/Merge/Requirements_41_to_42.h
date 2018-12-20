#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Requirements_1_to_3.h"
#include "Requirements_5.h"
#include "Requirement_6_to_12_and_15.h"
#include"Requirment_13_14.h"
#include"Requirement_21.h"

using namespace std;

typedef struct {
	string username;
	string id;
	string first_name;
	string last_name;
	int level;
	string phone_number;
	double salary;
	string is_excellent;
}Worker;


void Login();
bool isValid(string user, string pass);
void load_details(string user_name);
void menu(Worker* worker);
void general_worker(Worker* worker);
void shift_manager(Worker* worker);
void store_manager(Worker* worker);



void Login()
{
	bool flag = false;
	char exit;
	string user_name;
	string password;
	//getting user name and password from user
	do
	{
		cout << "Please enter your username" << endl;
		cin >> user_name;
		cout << "Please enter your password" << endl;
		cin >> password;
		//checking if user name and right password exists
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
	//checking in data base if user and password exsist and match
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
				UsersData >> worker->salary;
				UsersData >> worker->is_excellent;
				flag = true;
			}
		}
	}
	UsersData.close();
	menu(worker);
}
//first menu of worker, checks which level the employee have and choose the right menu
void menu(Worker* worker)
{
	int opt;
	switch (worker->level)
	{
	case 1:
	{
		system("cls");
		general_worker(worker);
		break;
	}
	case 2:
	{
		system("cls");
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
		store_manager(worker);
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
		cout << "welcome to employee menu" << endl;
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
				system("cls");
				creatBill(worker->id,worker->level);
				break;
			}
			case 2:
			{
				system("cls");
				Add_Club_Member(worker->id);
				break;
			}
			case 3:
			{
				productInStock();
				break;
			}
			case 4:
			{
				productPrice();
				break;
			}
			case 5:
			{
				locateTransaction();
				break;
			}
			case 6:
			{
				dailySalesReport(worker->id);
				break;
			}
			case 7:
			{
				dailyClubMebmer(worker->id);
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
		cout << "welcome to shift manager menu" << endl;
		cout << "press 1 to create bill" << endl;
		cout << "press 2 to add club member" << endl;
		cout << "press 3 to check if product in stock" << endl;
		cout << "press 4 to check product price" << endl;
		cout << "press 5 to locate transaction" << endl;
		cout << "press 6 to create your daily sells report" << endl;
		cout << "press 7 to create your daily club members report" << endl;
		cout << "press 8 to return product to store" << endl;
		cout << "press 9 to choose excellent worker bonus" << endl;
		cout << "press 10 to remove excellent worker bonus" << endl;
		cout << "press 11 to sale new giftcard" << endl;
		cout << "press 12 to create general daily sells report" << endl;
		cout << "press 13 to create daily return product report" << endl;
		cout << "press 0 to back" << endl;
		cin >> opt;
		switch (opt)
		{
			case 1:
			{
				system("cls");
				creatBill(worker->id,worker->level);
				break;
			}
			case 2:
			{
				system("cls");
				Add_Club_Member(worker->id);
				break;
			}
			case 3:
			{
				productInStock();
				break;
			}
			case 4:
			{
				productPrice();
				break;
			}
			case 5:
			{
				locateTransaction();
				break;
			}
			case 6:
			{
				dailySalesReport(worker->id);
				break;
			}
			case 7:
			{
				dailyClubMebmer(worker->id);
				break;
			}
			case 8:
			{
				returnProduct();
				break;
			}
			case 9:
			{
				system("cls");
				workerBonus();
				break;
			}
			case 10:
			{
				system("cls");
				removeBonus();
				break;
			}
			case 11:
			{
				saleNewGiftCard();
				break;
			}
			case 12:
			{
				dailyGeneralSalesReport();
				break;
			}
			case 13:
			{
				dailyReturnedProductReport();
				break;
			}
			case 14:
			{
				//zReport();
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
void store_manager(Worker* worker)
{
	int opt;
	bool flag = false;

	do
	{
		cout << "welcome to store manager menu" << endl;
		cout << "press 1 to create bill" << endl;
		cout << "press 2 to add club member" << endl;
		cout << "press 3 to check if product in stock" << endl;
		cout << "press 4 to check product price" << endl;
		cout << "press 5 to locate transaction" << endl;
		cout << "press 6 to create your daily sells report" << endl;
		cout << "press 7 to create your daily club members report" << endl;
		cout << "press 8 to return product to store" << endl;
		cout << "press 10 to remove excellent worker bonus" << endl;
		cout << "press 11 to sale new giftcard" << endl;
		cout << "press 12 to create general daily sells report" << endl;
		cout << "press 13 to create daily return product report" << endl;
		cout << "press 14 to change access to employee" << endl; //....
		cout << "press 15 to add amount of money to worker salary" << endl;
		cout << "press 0 to back" << endl;
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			system("cls");
			creatBill(worker->id,worker->level);
			break;
		}
		case 2:
		{
			system("cls");
			Add_Club_Member(worker->id);
			break;
		}
		case 3:
		{
			productInStock();
			break;
		}
		case 4:
		{
			productPrice();
			break;
		}
		case 5:
		{
			locateTransaction();
			break;
		}
		case 6:
		{
			dailySalesReport(worker->id);
			break;
		}
		case 7:
		{
			dailyClubMebmer(worker->id);
			break;
		}
		case 8:
		{
			returnProduct();
			break;
		}
		case 9:
		{
			workerBonus();
			break;
		}
		case 10:
		{
			removeBonus();
			break;
		}
		case 11:
		{
			saleNewGiftCard();
			break;
		}
		case 12:
		{
			dailyGeneralSalesReport();
			break;
		}
		case 13:
		{
			dailyReturnedProductReport();
			break;
		}
		case 14:
		{
			changeAccess();
			break;
		}
		case 15:
		{
			changeEmployeeSalary();
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
