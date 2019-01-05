#pragma once
#include "Requirements_5.h"
//this header contain delete and add employees , change salary and change level , report of excellent employee, locate employee , club member all time report.
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

string returnRole(int);
void deleteFromeUserAndPass(string); //signature only

bool checkIfValidId(string id)
{
	return(id.length() == 9 && checkIfNum(id));
}

bool checkIfWorkerFound(string id_to_compare) //check if worker exist in employee.txt
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

string changeEmployeeSalary(string test_id = "NO", string test_amount = "NO") //this func add amount of money to exist salary of employee
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
	if (test_id.compare("NO") == 0)
	{
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
	}
	do
	{
		if (test_id.compare("NO") == 0)
		{
			if (!flag)
			{
				cout << "Id invalid" << endl;
			}

			cout << "Enter employee id to change salary: ";
			cin >> id_to_change_salary;
		}
		else
		{
			id_to_change_salary = test_id;
		}

		if (!checkIfValidId(id_to_change_salary) || !checkIfWorkerFound(id_to_change_salary))
		{
			flag = false;
		}
		else
			flag = true;
	} while (!flag);
	do
	{
		if (test_amount.compare("NO") == 0)
		{
			if (!flag)
			{
				cout << "Amount invalid" << endl;
			}
			cout << "Enter amount of money to add to employee salary: ";
			cin >> amount_string;
		}
		else
		{
			amount_string = test_amount;
		}
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
	if (test_id.compare("NO") == 0)
	{
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
	if (test_id.compare("NO") != 0)
	{
		return "Update success";
	}
	else
	{
		return "Done";
	}


}

double returnChangeSalary(int level, int  level_to_change) { //change salary if level changed
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

string changeAccess(string test_id = "NO", char test_level = '6') //promote or Downgrade employee and change his salary.
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
	if (test_id.compare("NO") == 0)
	{
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
			cout << "Enter employee id to change access (-1 to back): ";
			cin >> id_access_to_change;
			if (id_access_to_change.compare("-1") == 0)
			{
				system("cls");
				cout << "You choose to go back" << endl;
				return "You choose to go back\n";
			}
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
	}
	else
	{
		id_access_to_change = test_id;
		level_to_change_char = test_level;
		level_to_change = level_to_change_char - '0';
		if (((!checkIfValidId(id_access_to_change) || !checkIfWorkerFound(id_access_to_change) || !checkIfNum(level_to_change_char) || (level_to_change_char <= '0' || level_to_change_char > '4'))))
			return "invalid change";
	}
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
	if (test_id.compare("NO") == 0)
	{
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
	return "Access successfully update";
}

void addNewEmployee() //add new employee to system with his full detail , level , user and password and update it in the relevant txt
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
void deleteExistEmployee() //delete employee if he exist 
{
	
	Employee* worker = new Employee;
	string file_user;
	string file_user2;
	string user_to_remove;
	bool flag = true;
	ifstream Input;
	ofstream Output;
	string id;
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
	do {
		cout << "Enter id of employee that you want to remove (-1 to back): " << endl;
		cin >> id;
		if (id.compare("-1") == 0)
		{
			system("cls");
			cout << "You choose to go back" << endl;
		}
			if (!checkIfWorkerFound(id))
				cout << "Worker not found, please try again" << endl;
		}while (!checkIfWorkerFound(id)&& id.compare("-1") != 0);
		if (id.compare("-1") != 0)
		{
			system("cls");
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
}
void deleteFromeUserAndPass(string user_to_remove) //after delete from employee.txt delete from txt of user and pass
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
			continue;
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
void ExcellentWorkersReport() //generate report (only 1 excellent worker at the same time) of excellent employee
{
	system("cls");
	Employee* worker = new Employee;
	ifstream Input;
	bool flag = false;
	Input.open("Employee.txt");
	if (Input)
	{
		Input >> worker->username;
		while (!Input.eof())
		{
			Input >> worker->id;
			Input >> worker->first_name;
			Input >> worker->last_name;
			Input >> worker->level;
			Input >> worker->phone_number;
			Input >> worker->salary;
			Input >> worker->is_excellent;
			if ((worker->is_excellent.compare("Yes") == 0) && !(flag))
			{
				flag = true;
				cout << "The current excellent employee is: \n" << worker->id << ' ' << worker->first_name << ' ' << worker->last_name << endl << endl;
			}
			Input >> worker->username;
		}
		if (!flag)
		{
			cout << "there is no excellent worker right now" << endl;
		}
		Input.close();
	}
}
string locateEmployee(string test_id="NO") //check if employee exist
{
	system("cls");
	ifstream Input;
	Employee* worker = new Employee;
	string role;
	string id;
	bool Found_Flag = false;
	if (test_id.compare("NO") == 0)
	{
		do {
			cout << "Enter id of employee that you want to see his details" << endl;
			cin >> id;
			if (!checkIfWorkerFound(id))
				cout << "Worker not found, please try again" << endl;
		} while (!checkIfWorkerFound(id));
	}
	else 
	{
		id = test_id;
	}
	Input.open("Employee.txt");
	if (Input)
	{
		Input >> worker->username;
		while (!Input.eof())
		{
			Input >> worker->id;
			Input >> worker->first_name;
			Input >> worker->last_name;
			Input >> worker->level;
			role = returnRole(worker->level);
			Input >> worker->phone_number;
			Input >> worker->salary;
			Input >> worker->is_excellent;
			if (worker->id.compare(id) == 0)
			{
				if (test_id.compare("NO") == 0)
				{
					cout << worker->username << ' ' << worker->id << ' ' << worker->first_name << ' ' << worker->last_name << ' ' << role << ' '
						<< worker->phone_number << ' ' << worker->salary << ' ' << worker->is_excellent << endl << endl;
				}
				Found_Flag = true;
				break;
			}
			Input >> worker->username;
		}
		Input.close();
		if (Found_Flag)
		{
			return worker->phone_number;
		}
		else
		{
			if (test_id.compare("NO") == 0)
			{
				cout << "Worker not found" << endl;
			}
			return"Worker not found";
		}
	}
}

string returnRole(int num) //return role of employee 
{
	string role;
	switch (num)
	{
		case 1:
		{
			role = "General-worker";
			break;
		}
		case 2:
		{
			role = "Shift-manager";
			break;
		}
		case 3:
		{
			role = "Supply-manager";
			break;
		}
		case 4:
		{
			role = "Store-manger";
			break;
		}
		default:
		{
			break;
		}
	}
	return role;
}
void allTimeClubMemeberReport() //generate club member report of all time
{
	system("cls");
	ifstream Input;
	string file_data;
	string Member_id;
	string Member_First_Name;
	string Member_Last_Name;
	string Member_Bday;
	string Member_add;
	string Member_phone;
	string Member_Additon_Date;
	string Worker_add_id;


	Input.open("ClubMember.txt");
	if (Input)
	{
		cout << "Club members of our store:" << endl;
		cout << "Member id:\tMember first name:\tMember last name:" << endl;
		while (!Input.eof())
		{
			Input >> Member_id;
				if (!Input.eof())
				{
					Input >> Member_First_Name;
					Input >> Member_Last_Name;
					Input >> Member_Bday;
					Input >> Member_add;
					Input >> Member_phone;
					Input >> Member_Additon_Date;
					Input >> Worker_add_id;
					cout << Member_id << "\t" << Member_First_Name << "\t\t\t" << Member_Last_Name << endl;
				}
		}
			
	}
		Input.close();
}
void salaryReport() //print the total amount of salary that the store pays
{
	system("cls");
	cout << "Salary report of store: " << endl;
	Employee* worker = new Employee;
	ifstream Input;
	bool flag = false;
	double totalSalary=0;
	Input.open("Employee.txt");
	if (Input)
	{
		Input >> worker->username;
		while (!Input.eof())
		{
			Input >> worker->id;
			Input >> worker->first_name;
			Input >> worker->last_name;
			Input >> worker->level;
			Input >> worker->phone_number;
			Input >> worker->salary;
			totalSalary += worker->salary;
			Input >> worker->is_excellent;
			cout << "Worker:" << worker->id  << ' ' << worker->first_name << ' ' << worker->last_name << ' ' << "Salary:" << worker->salary << endl;
			Input >> worker->username;
		}
		cout << "Total salary of all employees: " << totalSalary << endl << endl;
		Input.close();
	}
}