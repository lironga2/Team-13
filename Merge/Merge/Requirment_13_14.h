#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "Requirement_6_to_12_and_15.h"

using namespace std;

void removeBonus();
void workerBonus();

void removeBonus()
{
	string username;
	string id;
	string first_name;
	string last_name;
	int level;
	string phone_number;
	double salary;
	string is_excellent;
	bool flag = true;
	ifstream Input;
	ofstream Output;
	Input.open("Employee.txt");
	Output.open("Temp.txt");
	bool Change_Flag = false;
	while (!Input.eof())
	{
		if (flag)
		{
			Input >> username;
		}
		Input >> id;
		Input >> first_name;
		Input >> last_name;
		Input >> level;
		Input >> phone_number;
		Input >> salary;
		Input >> is_excellent;
		if (is_excellent.compare("No") != 0)
		{
			salary -= 1000;
			is_excellent = "No";
			Change_Flag = true;
		}
		Output << username << ' ';
		Output << id << ' ';
		Output << first_name << ' ';
		Output << last_name << ' ';
		Output << level << ' ';
		Output << phone_number << ' ';
		Output << salary << ' ';
		Output << is_excellent;
		Input >> username;
		flag = false;
		if (!Input.eof())
		{
			Output << endl;
		}

	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Employee.txt");
	string transfer;
	while (!Input.eof())
	{
			Input >> transfer;
			Output << transfer << ' ';
			if (transfer.compare("Yes") == 0 || transfer.compare("No") == 0)
			{
				Output << endl;
			}
	}
	Input.close();
	Output.close();
	system("cls");
	if (Change_Flag)
	{
		cout << "Bonus has been removed" << endl;
	}
	else
	{
		cout << "There is no excellent worker" << endl;
	}
}

void workerBonus()
{
	string id_to_compare;
	string transfer;
	string username;
	string id;
	string first_name;
	string last_name;
	int level;
	string phone_number;
	double salary;
	string is_excellent;
	bool flag = false;
	ifstream Input;
	ofstream Output;
	string Excellent = "No";
	Input.open("Employee.txt");
	//check if there is an excellent worker
	while (!Input.eof())
	{
		Input >> is_excellent;
		if (is_excellent.compare("Yes") == 0)
		{
			flag = true;
			system("cls");
			cout << "There is an excellent worker - for re-choose remove the exsisting choosen and try again" << endl;
			break;
		}
	}
	Input.close();
	if (!flag)
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
				if (transfer.compare("No") == 0)
				{
					cout << endl;
				}
				Input >> transfer;
				input_flag = false;
		}
		bool id_valid_flag = true;
		do
		{
			if (!id_valid_flag)
			{
				cout << "Id invalid" << endl;
			}
			cout << "Enter worker ID number:" << endl;
			cin >> id_to_compare;
			if (id_to_compare.length() != 9)
			{
				id_valid_flag = false;
			}
		} while (id_to_compare.length() != 9);
		Input.close();
		Input.open("Employee.txt");
		Output.open("Temp.txt");
		bool Endl_Flag = true;
		while (!Input.eof())
		{
			if (Endl_Flag)
			{
				Input >> username;
			}
			Input >> id;
			Input >> first_name;
			Input >> last_name;
			Input >> level;
			Input >> phone_number;
			Input >> salary;
			Input >> is_excellent;
			if (id.compare(id_to_compare) == 0)
			{
				salary += 1000;
				is_excellent = "Yes";
			}
			Output << username << ' ';
			Output << id << ' ';
			Output << first_name << ' ';
			Output << last_name << ' ';
			Output << level << ' ';
			Output << phone_number << ' ';
			Output << salary << ' ';
			Output << is_excellent;
			Input >> username;
			Endl_Flag = false;
			if (!Input.eof())
			{
				Output << endl;
			}

		}
		Input.close();
		Output.close();
		Input.open("Temp.txt");
		Output.open("Employee.txt");
		while (!Input.eof())
		{
			Input >> transfer;
			Output << transfer << ' ';
			if (transfer.compare("Yes") == 0 || transfer.compare("No") == 0)
			{
				Output << endl;
			}
		}
		Input.close();
		Output.close();
		system("cls");
		cout << "Bonus has been added" << endl;
	}
}
