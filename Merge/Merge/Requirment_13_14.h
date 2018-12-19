#pragma once
#include "Requirement_6_to_12_and_15.h"

using namespace std;

void removeBonus();

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

	ifstream Input;
	ofstream Output;
	string Excellent = "No";
	Input.open("Employee.txt");
	Output.open("Temp.txt");
	while (!Input.eof())
	{
		Input >> username;
		Input >> id;
		Input >> first_name;
		Input >> last_name;
		Input >> level;
		Input >> phone_number;
		Input >> salary;
		Input >> is_excellent;
		if (is_excellent.compare(Excellent) != 0)
		{
			salary -= 1000;
			is_excellent = Excellent;
		}
		Output << username << ' ';
		Output << id << ' ';
		Output << first_name << ' ';
		Output << last_name << ' ';
		Output << level << ' ';
		Output << phone_number << ' ';
		Output << salary << ' ';
		Output << is_excellent << endl;
	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Employee.txt");
	string transfer;
	while (!Input.eof())
	{
		if (!Input.eof())
		{
			Input >> transfer;
			Output << transfer << ' ';
			if (transfer.compare("Yes") == 0 || transfer.compare("No") == 0)
			{
				Output << endl;
			}
		}
	}
	Input.close();
	Output.close();
}