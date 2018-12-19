#pragma once
#include "Requirement_6_to_12_and_15.h"
#include"Requirements_41_to_42.h"
using namespace std;

void removeBonus()
{
	ifstream Input;
	ofstream Output;
	double Salary;
	string Excellent = "No";
	Input.open("Employee.txt");
	Output.open("Temp.txt");
	Worker *Emploee = new Worker;
	while (!Input.eof())
	{
		Input >> Emploee->id;
		Input >> Emploee->first_name;
		Input >> Emploee->last_name;
		Input >> Emploee->level;
		Input >> Emploee->phone_number;
		Input >> Emploee->salary;
		Input >> Emploee->is_excellent;
	}
}