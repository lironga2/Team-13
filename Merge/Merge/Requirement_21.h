#pragma once
#include "Requirements_5.h"
typedef struct {
	string username;
	string id;
	string first_name;
	string last_name;
	int level;
	string phone_number;
	double salary;
	string is_excellent;
}Employee;

void deleteFromeUserAndPass(string); //signature only

bool checkIfValidId(string id)
{
	return(id.length() == 9 && checkIfNum(id));
}
bool checkIfWorkerFound(string id_to_compare)
{
	ifstream Input;
	string transfer;

	Input.open("Employee.txt");
	bool input_flag = true;
	while (!Input.eof())
	{
		if (transfer.compare(id_to_compare) == 0)
		{
			return true;
		}
		Input >> transfer;
	}
	Input.close();
	return false;
}

void changeEmployeeSalary()  
{
	Employee* worker = new Employee;
	string file_user;
	bool flag = true;
	ifstream Input;
	string transfer;
	ofstream Output;
	string id_to_change_salary;
	string amount_string;
	double amount;
	
	cout << "Workers list:" << endl;
	Input.open("Employee.txt");
	Input >> transfer;
	while (!Input.eof())
	{
		if (!Input.eof())
		{
			if ((transfer.compare("Yes") == 0) || (transfer.compare("No") == 0))
				cout << transfer << endl;
			else
				cout << transfer << ' ';
		}
		Input >> transfer;
	}
	Input.close();
	do
	{
		if (!flag)
		{
			cout << "Id invalid" << endl;
		}
		
		cout << "Enter employee id to change salary: ";
		cin >> id_to_change_salary;

		if (!checkIfValidId(id_to_change_salary) || !checkIfWorkerFound(id_to_change_salary))
		{
			flag = false;
		}
		else
			flag = true;
	} while (!flag);
	do
	{
		if (!flag)
		{
			cout << "Amount invalid" << endl;
		}
		cout << "Enter amount of money to add to employee salary: ";
		cin >> amount_string;

		if (!checkIfNum(amount_string))
		{
			flag = false;
		}
		else
		{
			flag = true;
			amount = convertStringToNum(amount_string);
		}
	} while (!flag);

	Output.open("Temp.txt");
	Input.open("Employee.txt");
	if (Input.is_open())
	{
		while (!Input.eof())
		{
			Input >> file_user;
			if (!Input.eof()) {
				if (id_to_change_salary.compare(file_user) == 0)
				{
					Input >> worker->first_name;
					Input >> worker->last_name;
					Input >> worker->level;
					Input >> worker->phone_number;
					Input >> worker->salary;
					worker->salary += amount;
					Input >> worker->is_excellent;
					Output << file_user << ' ';
					Output << worker->id << ' ';
					Output << worker->first_name << ' ';
					Output << worker->last_name << ' ';
					Output << worker->level << ' ';
					Output << worker->phone_number << ' ';
					Output << worker->salary << ' ';
					Output << worker->is_excellent << endl;
				}
				else
				{

					if ((file_user.compare("Yes") == 0) || (file_user.compare("No") == 0))
						Output << file_user << endl;
					else
						Output << file_user << ' ';
				}
			}
		}
	}
	Input.close();
	Output.close();
	Output.open("Employee.txt");
	Input.open("Temp.txt");
	Input >> file_user;
	while (!Input.eof())
	{
		if (!Input.eof())
		{
			Output << file_user << ' ';
			if ((file_user.compare("Yes") == 0) || (file_user.compare("No") == 0))
				Output << endl;
			Input >> file_user;
		}
	}
	Input.close();
	Output.close();


}

double returnChangeSalary(int level, int  level_to_change) {
	double ChangeSalary = 0;
	if ((level == 1 && level_to_change == 2) || (level == 2 && level_to_change == 1)) {
		if (level == 1 && level_to_change == 2) {
			ChangeSalary += 3000;
		}
		if (level == 2 && level_to_change == 1) {
			ChangeSalary -= 3000;
		}
	}
	if ((level == 1 && level_to_change == 3) || (level == 3 && level_to_change == 1)) {
		if (level == 1 && level_to_change == 3) {
			ChangeSalary += 5000;
		}
		if (level == 3 && level_to_change == 1) {
			ChangeSalary -= 5000;
		}
	}
	if ((level == 1 && level_to_change == 4) || (level == 4 && level_to_change == 1)) {
		if (level == 1 && level_to_change == 4) {
			ChangeSalary += 7000;
		}
		if (level == 4 && level_to_change == 1) {
			ChangeSalary -= 7000;
		}
	}
	if ((level == 2 && level_to_change == 4) || (level == 4 && level_to_change == 2)) {
		if (level == 2 && level_to_change == 4) {
			ChangeSalary += 4000;
		}
		if (level == 4 && level_to_change == 2) {
			ChangeSalary -= 4000;
		}
	}
	if ((level == 2 && level_to_change == 3) || (level == 3 && level_to_change == 2)) {
		if (level == 2 && level_to_change == 3) {
			ChangeSalary += 2000;
		}
		if (level == 3 && level_to_change == 2) {
			ChangeSalary -= 2000;
		}
	}
	return ChangeSalary;
}

void changeAccess()
{
	Employee* worker = new Employee;
	string file_user;
	bool flag = true;
	ifstream Input;
	ofstream Output;
	string id_access_to_change;
	int level_to_change;
	char level_to_change_char;
	string transfer;
	
	cout << "Workers list:" << endl;
	Input.open("Employee.txt");
	bool input_flag = true;
	while (!Input.eof())
	{
		if (input_flag)
		{
			Input >> transfer;
		}
		cout << transfer << ' ';
		if (transfer.compare("No") == 0 || transfer.compare("Yes") == 0)
		{
			cout << endl;
		}
		Input >> transfer;
		input_flag = false;
	}
	Input.close();
		do
		{
			if (!flag)
			{
				cout << "Id invalid" << endl;
			}
			cout << "Enter employee id to change access: ";
			cin >> id_access_to_change;
			
			if (!checkIfValidId(id_access_to_change) || !checkIfWorkerFound(id_access_to_change))
			{
				flag = false;
			}
			else
				flag = true;
		} while (!flag);
		do 
		{
			if (!flag)
			{
				cout << "Level invalid" << endl;
			}
			cout << "Enter level to change: ";
			cin >> level_to_change_char;
			
			if (!checkIfNum(level_to_change_char) || (level_to_change_char <= '0' || level_to_change_char > '4'))
			{
				flag = false;
			}
			else {
				flag = true;
				level_to_change = level_to_change_char - '0';
			}
		} while (!flag);

	Output.open("Temp.txt");
	Input.open("Employee.txt");
	if (Input.is_open())
	{
		while (!Input.eof())
		{
			Input >> file_user;
			if (!Input.eof()) {
				if (id_access_to_change.compare(file_user) == 0)
				{
					Input >> worker->first_name;
					Input >> worker->last_name;
					Input >> worker->level;
					Input >> worker->phone_number;
					Input >> worker->salary;
					worker->salary += returnChangeSalary(worker->level, level_to_change);
					Input >> worker->is_excellent;
					Output << file_user << ' ';
					Output << worker->id << ' ';
					Output << worker->first_name << ' ';
					Output << worker->last_name << ' ';
					Output << level_to_change << ' ';
					Output << worker->phone_number << ' ';
					Output << worker->salary << ' ';
					Output << worker->is_excellent << endl;
				}
				else
				{

					if ((file_user.compare("Yes") == 0) || (file_user.compare("No") == 0))
						Output << file_user << endl;
					else
						Output << file_user << ' ';
				}
			}
		}
	}
	Input.close();
	Output.close();
	Output.open("Employee.txt");
	Input.open("Temp.txt");
	Input >> file_user;
	while (!Input.eof())
	{
		if (!Input.eof()) 
		{
			Output << file_user << ' ';
			if ((file_user.compare("Yes") == 0) || (file_user.compare("No") == 0))
				Output << endl;
			Input >> file_user;
		}
	}
	Input.close();
	Output.close();
}
void addNewEmployee() 
{
	Employee* worker = new Employee;
	ifstream Input;
	ofstream Output;
	bool flag = true;
	string password;
	cout << "enter employee details" << endl;
	cout << "Enter eployee username" << endl;
	cin >> worker->username;
	cout << "Enter employee password" << endl;
	cin >> password;
	do
	{
		cout << "Enter eployee id" << endl;
		cin >> worker->id;
		if (checkIfWorkerFound(worker->id))
			cout << "Worker already registered in the system,please try again" << endl;
		if (!checkIfValidId(worker->id))
			cout << "Id is not valid, please try again." << endl;
	} while (checkIfWorkerFound(worker->id) || !checkIfValidId(worker->id));
	cout << "Enter eployee first name" << endl;
	cin >> worker->first_name;
	cout << "Enter eployee last name" << endl;
	cin >> worker->last_name;
	cout << "Enter eployee level access (1=general worker, 2= shift manager , 3= supply manager 4= store manager)" << endl;
	cin >> worker->level;
	cout << "Enter eployee phone number" << endl;
	cin >> worker->phone_number;
	cout << "Enter eployee basic salary" << endl;
	cin >> worker->salary;
	worker->is_excellent= "No";


	Output.open("Employee.txt", std::fstream::app);
	Output << worker->username << ' ' << worker->id << ' ' << worker->first_name << ' ' << worker->last_name << ' ' << worker->level << ' ' <<
		worker->phone_number << ' ' << worker->salary << ' ' << worker->is_excellent << endl;
	Output.close();
	Output.open("UserAndPass.txt",std::fstream::app);
	Output << worker->username << ' ' << password << endl;
	Output.close();
}
void deleteExistEmployee() /// need to fixed
{
	system("cls");
	Employee* worker = new Employee;
	string file_user;
	string file_user2;
	string user_to_remove;
	bool flag = true;
	ifstream Input;
	ofstream Output;
	string id;
	do {
		cout << "Enter id of employee that you want to remove" << endl;
		cin >> id;
		if (!checkIfWorkerFound(id))
			cout << "Worker not found, please try again" << endl;
	}while (!checkIfWorkerFound(id));
	
	cout << "User and his details has been deleted from the system" << endl;
	Output.open("Temp.txt");
	Input.open("Employee.txt");

	while (!Input.eof())
	{
		Input >> worker->username;
		Input >> worker->id;
		Input >> worker->first_name;
		Input >> worker->last_name;
		Input >> worker->level;
		Input >> worker->phone_number;
		Input >> worker->salary;
		Input >> worker->is_excellent;
		if (id.compare(worker->id) == 0)
		{
			user_to_remove = worker->username;
		}
		else
		{
			Output << worker->username << ' ' << worker->id << ' ' << worker->first_name << ' ' << worker->last_name << ' ' <<
			worker->level << ' ' << worker->phone_number << ' ' << worker->salary << ' ' << worker->is_excellent << endl;
		}
	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Employee.txt");
	Input >> file_user;
	while (!Input.eof())
	{
		if ((file_user.compare("Yes") == 0) || (file_user.compare("No") == 0))
		{
			Output << file_user << endl;
		}
		else
		{
			Output << file_user << ' ';
		}
		Input >> file_user;
	}
	Input.close();
	Output.close();
	deleteFromeUserAndPass(user_to_remove);

}
void deleteFromeUserAndPass(string user_to_remove)
{
	ifstream Input;
	ofstream Output;
	string file_data;

	Input.open("UserAndPass.txt");
	Output.open("Temp.txt");
	Input >> file_data;
	while (!Input.eof())
	{
		if (file_data.compare(user_to_remove) == 0)
		{
			Input >> file_data;
			Input >> file_data;
		}
		else
		{
			Output << file_data << ' ';
			Input >> file_data;
			Output << file_data << endl;
			Input >> file_data;
		}
	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("UserAndPass.txt");
	Input >> file_data;
	while (!Input.eof())
	{
		Output << file_data << ' ';
		Input >> file_data;
		Output << file_data << endl;
		Input >> file_data;
	}
	Input.close();
	Output.close();
}
