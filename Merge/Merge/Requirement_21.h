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
		do
		{
			if (!flag)
			{
				cout << "Id invalid" << endl;
			}
			cout << "Enter employee id to change access: ";
			cin >> id_access_to_change;
			if (id_access_to_change.length() != 9 || !checkIfNum(id_access_to_change))
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
				level_to_change = int(level_to_change_char);
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