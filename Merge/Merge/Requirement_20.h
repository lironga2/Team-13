#pragma once
#include<iostream>
#include<fstream>
#include<string>
//#include"Requirement_26.h"

using namespace std;

void Z_Report_Close_Cashbox(string todaydate)
{

	double Bill_Amount;
	double Today_Money = 0;
	double CashBox = 0;
	string Transfer;
	string Check;
	string date_to_compare;
	double Amount;
	string Transaction_Number;
	ifstream Input;
	ofstream Output;
	ifstream Transaction;
	int The_Number = 1;
	cout << "--------------------------------------------------------------------" << endl;
	cout << "Z REPORT OF THE DAY " << todaydate << endl;
	Transaction.open("Transaction.txt");
	while (!Transaction.eof())
	{
		Transaction >> Transfer;
		if (!Transaction.eof())
		{
			Transaction >> date_to_compare;
			Transaction >> Check;
			if (date_to_compare.compare(todaydate) == 0)
			{
				cout <<"Transction number: "<< The_Number << ") " <<':'<< endl;
				The_Number ++;
				while (!Transaction.eof())
				{
					Transaction >> Transfer;
					if (!Transaction.eof())
					{
						if (Transfer[0] == '#')
						{
							break;
						}
						Transaction >> date_to_compare;
						Transaction >> Check;
						cout << Transfer << ' ' << date_to_compare << ' ' << Check << endl;
					}
				}
			}
		}
	}
	Transaction.close();
	Transaction.open("GiftCard.txt");
	The_Number = 1;
	while (!Transaction.eof())
	{
		Transaction >> Transaction_Number;
		if (!Transaction.eof())
		{
			Transaction >> Amount;
			Transaction >> date_to_compare;
			if (date_to_compare.compare(todaydate) == 0)
			{
				cout << "GiftCard Transction number: " << The_Number << ") " << ':' << endl;
				The_Number ++ ;
				cout  <<"Payment: " <<Amount << endl;
				Today_Money += Amount;
			}
		}
	}
	Transaction.close();
	Transaction.open("Transaction.txt");
	while (!Transaction.eof())
	{
		Transaction >> Transfer;
		if (Transfer.compare(todaydate) == 0)
		{
			Transaction >> Transfer;
			while (!Transaction.eof() && Transfer[0] != '#')
			{
				Transaction >> Transfer;
				if (Transfer.compare("bill:") == 0)
				{
					Transaction >> Bill_Amount;
					Today_Money += Bill_Amount;
					break;
				}
			}
		}
	}
	Transaction.close();

	Input.open("Financial balance.txt");
	Output.open("Temp.txt");
	while (!Input.eof())
	{	
		Input >> Transfer;
		if (!Input.eof())
		{
			if (Transfer.compare("revenue:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("box:") == 0)
			{
				Output << Transfer << ' ';
				Input >> CashBox;
				CashBox += Today_Money;
				Output << CashBox << endl;
				continue;
			}
			if (Transfer.compare("expenses:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("money:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("sale:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			Output << Transfer << ' ';
		}
	}
	cout << "today total store revenue: " << Today_Money << endl;
	cout << "--------------------------------------------------------------------" << endl;
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Financial balance.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
		if (!Input.eof())
		{
			if (Transfer.compare("revenue:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("box:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("expenses:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("money:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("sale:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			Output << Transfer << ' ';
		}
	}
	Input.close();
	Output.close();

}
