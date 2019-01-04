#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Requirements_1_to_3.h"
#include"Requirements_5.h"
#include"Requirement_6_to_12_and_15.h"
#include"Requirment_13_14.h"
#include"Requirement_21.h"
#include"Requirement_20.h"
#include"Requirement_34.h"
#include"Requirement_39.h"
#include"Requirement_38.h"
#include"Requirement_37.h"
#include"Requirement_35.h"
#include"Requirement_31_to_33.h"
#include"Requirement_40.h"
//#include"Requirement_26.h"

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


string Login(string test_user_name = "NO", string test_password = "NO");
bool isValid(string user, string pass);
string load_details(string user_name, string test = "NO");
void menu(Worker* worker);
void general_worker(Worker* worker);
void shift_manager(Worker* worker);
void store_manager(Worker* worker);
void procurement_manager(Worker * worker);



string Login(string test_user_name,string test_password) //login to system
{
	bool flag = false;
	char exit;
	string user_name;
	string password;
	//getting user name and password from user
	if (test_user_name.compare("NO") == 0)
	{
		do
		{
			system("cls");
			cout << "Please enter your username" << endl;
			cin >> user_name;
			cout << "Please enter your password" << endl;
			cin >> password;
			//checking if user name and right password exists
			if (isValid(user_name, password))
			{
				system("cls");
				cout << "You have been connected to:";
				flag = true;
			}
			else
			{
				system("cls");
				cout << "User name or password are incorrect" << endl;
				cout << "If you want try again press Y or y to exit press any other key" << endl;
				cin >> exit;
			}
		} while ((!flag) && ((exit == 'y') || (exit == 'Y')));
	}
	else
	{
		if(isValid(test_user_name, test_password))
			return "your log to system";
		return "invalid";
	}
	if (flag)
	{
		load_details(user_name);
	}
	return "GECM software solutions ltd :)\n";
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
				UsersData.close();
				return true;
			}
		}
		UsersData.close();
		return false;
	}
}


string load_details(string user_name,string test)
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
	if (test.compare("NO") == 0)
	{
		cout << worker->first_name << ' ' << worker->last_name << endl;
		menu(worker);
		return "0";
	}
	return worker->first_name;
}
//first menu of worker, checks which level the employee have and choose the right menu
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
		procurement_manager(worker);
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
	string Option;
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
		cout << "press 0 to logout" << endl;
		cin >> Option;
		opt = convertStringToNum(Option);
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
				system("cls");
				productInStock();
				break;
			}
			case 4:
			{
				system("cls");
				productPrice();
				break;
			}
			case 5:
			{
				system("cls");
				locateTransaction();
				break;
			}
			case 6:
			{
				system("cls");
				dailySalesReport(worker->id);
				break;
			}
			case 7:
			{
				system("cls");
				dailyClubMebmer(worker->id);
				break;
			}
			case 0:
			{
				Login();
				flag = true;
				break;
			}
			default:
				system("cls");
				cout << "Option invalid try again" << endl;
				break;
		}
	} while (!flag);
}
void shift_manager(Worker* worker)
{
	string Option;
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
		cout << "press 14 to create z report and close the cash box" << endl;
		cout << "press 0 to logout" << endl;
		cin >> Option;
		opt = convertStringToNum(Option);
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
				system("cls");
				productInStock();
				break;
			}
			case 4:
			{
				system("cls");
				productPrice();
				break;
			}
			case 5:
			{
				system("cls");
				locateTransaction();
				break;
			}
			case 6:
			{
				system("cls");
				dailySalesReport(worker->id);
				break;
			}
			case 7:
			{
				system("cls");
				dailyClubMebmer(worker->id);
				break;
			}
			case 8:
			{
				system("cls");
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
				//fix make payment.
				system("cls");
				saleNewGiftCard();
				break;
			}
			case 12:
			{
				system("cls");
				dailyGeneralSalesReport();
				break;
			}
			case 13:
			{
				system("cls");
				dailyReturnedProductReport();
				break;
			}
			case 14:
			{
				system("cls");
				UpdateDate();
				string today = currDate;
				Z_Report_Close_Cashbox(today);
				break;
			}
			case 0:
			{
				Login();
				flag = true;
				break;
			}
			default:
				system("cls");
				cout << "Option invalid try again" << endl;
				break;
		}
	} while (!flag);

}

void procurement_manager(Worker * worker)
{
	string Option;
	int opt;
	bool flag = false;

	do
	{
		cout << "welcome to procurement manager menu" << endl;
		cout << "press 1 to create new order" << endl;
		cout << "press 2 to add product to stock" << endl;
		cout << "press 3 to delete product from stock" << endl;
		cout << "press 4 to change product price" << endl;
		cout << "press 5 to view sells report " << endl;
		cout << "press 6 to generate missing product in stock report" << endl;
		cout << "press 7 to generate product in stock report" << endl;
		cout << "press 8 to generate orders report" << endl;
		cout << "press 0 to logout" << endl;
		cin >> Option;
		opt = convertStringToNum(Option);
		switch (opt)
		{
		case 1:
		{
			Create_New_Order();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			Add_Product_To_Stock();
			break;
		}
		case 3:
		{
			system("cls");
			Remove_Product_From_Stock();
			break;
		}
		case 4:
		{
			system("cls");
			changeProductPrice();
			break;
		}
		case 5:
		{
			system("cls");
			General_Sells_Report();
			break;
		}
		case 6:
		{
			system("cls");
			Stock_Shortage();
			break;
		}
		case 7:
		{
			system("cls");
			Stock_Report();
			break;
		}
		case 8:
		{
			system("cls");
			Orders_Report();
			break;
		}
		case 0:
		{
			Login();
			flag = true;
			break;
		}
		default:
			system("cls");
			cout << "Option invalid try again" << endl;
			break;
		}
	} while (!flag);
}

void store_manager(Worker* worker)
{
	string Option;
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
		cout << "press 6 to return product to store" << endl;
		cout << "press 7 to choose excellent worker bonus" << endl;
		cout << "press 8 to remove excellent worker bonus" << endl;
		cout << "press 9 to sale new giftcard" << endl;
		cout << "press 10 to change access to employee" << endl; //....
		cout << "press 11 to add new employee" << endl;
		cout << "press 12 to remove exist employee" << endl;
		cout << "press 13 to add amount of money to worker salary" << endl;
		cout << "press 14 to sale management" << endl;
		cout << "press 15 to locate employee" << endl;
		cout << "press 16 to generate reports menu" << endl;
		cout << "press 0 to logout" << endl;
		cin >> Option;
		opt = convertStringToNum(Option);
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
			system("cls");
			productInStock();
			break;
		}
		case 4:
		{
			system("cls");
			productPrice();
			break;
		}
		case 5:
		{
			system("cls");
			locateTransaction();
			break;
		}
		case 6:
		{
			system("cls");
			returnProduct();
			break;
		}
		case 7:
		{
			system("cls");
			workerBonus();
			break;
		}
		case 8:
		{
			system("cls");
			removeBonus();
			break;
		}
		case 9:
		{
			system("cls");
			saleNewGiftCard();
			break;
		}
		case 10:
		{
			system("cls");
			changeAccess();
			break;
		}
		case 11:
		{
			system("cls");
			addNewEmployee();
			break;
		}
		case 12:
		{
			system("cls");
			deleteExistEmployee();
			break;
		}
		case 13:
		{
			system("cls");
			changeEmployeeSalary();
			break;
		}
		case 14:
		{
			system("cls");
			Sale_Management(&ifSale, &Sale_Percent, &sale);
			break;
		}
		case 15:
		{
			system("cls");
			locateEmployee();
			break;
		}
		case 16:
		{
			string Report_Chocie;
			int Report_Option;
			bool Report_Flag = true;

			do
			{
				cout << "welcome to generate reports menu" << endl;
				cout << "press 1 to create your daily sells report" << endl;
				cout << "press 2 to create your daily club members report" << endl;
				cout << "press 3 to create general daily sells report" << endl;
				cout << "press 4 to create daily return product report" << endl;
				cout << "press 5 to create z report and close the cash box" << endl;
				cout << "press 6 to generate all-time club members report" << endl;
				cout << "press 7 to check which employee is excellent" << endl;
				cout << "press 8 to generate salary report of all employees" << endl;
				cout << "press 0 to back" << endl;
				cin >> Report_Chocie;
				Report_Option = convertStringToNum(Report_Chocie);
				switch (Report_Option)
				{
					case 1:
					{
						system("cls");
						dailySalesReport(worker->id);
						break;
					}
					case 2:
					{
						system("cls");
						dailyClubMebmer(worker->id);
						break;
					}
					case 3:
					{
						system("cls");
						dailyGeneralSalesReport();
						break;
					}
					case 4:
					{
						system("cls");
						dailyReturnedProductReport();
						break;
					}
					case 5:
					{
						system("cls");
						UpdateDate();
						string today = currDate;
						Z_Report_Close_Cashbox(today);
						break;
					}
					case 6:
					{
						system("cls");
						allTimeClubMemeberReport();
						break;
					}
					case 7:
					{
						system("cls");
						ExcellentWorkersReport();
						break;
					}
					case 8:
					{
						system("cls");
						salaryReport();
						break;
					}
					case 0:
					{
						system("cls");
						Report_Flag = false;
						break;
					}
					default:
						system("cls");
						cout << "Option invalid try again" << endl;
						break;
					}

			} while (Report_Flag);
			break;
		}
		case 0:
		{
			Login();
			flag = true;
			break;
		}
		default:
			system("cls");
			cout << "Option invalid try again" << endl;
			break;
		}
	} while (!flag);
}
