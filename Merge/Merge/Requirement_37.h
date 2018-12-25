#pragma once
#include<string>
#include <iostream>
#include<fstream>

using namespace std;

void General_Sells_Report()
{
	ifstream Input;
	string Temp1;
	string Temp2;
	string Temp3;
	bool product_flag = true;
	bool transaction_flag = true;
	Input.open("Transaction.txt");
	while (!Input.eof())
	{
		Input >> Temp1;
		if (!Input.eof())
		{
			Input >> Temp2;
			Input >> Temp3;
			if (Temp1[0] == '#')
			{
				cout << "Number of Transaction\t" << "Date \t\tWOrker id" << endl;
				cout << Temp1 << "\t\t\t" << Temp2 << '\t' << Temp3 << endl << endl;
				cout << "product cct\t" << "  " << "product name\tproduct amount" << endl;
				//cout << "----------------------------------------------" << endl;
				continue;
			}
			if (Temp1.compare("Total") == 0)
			{
				cout << Temp1 << ' ' << Temp2 << ' '<< Temp3 << endl;
				cout << "----------------------------------------------" << endl;
				continue;
			}
			else
			{
				cout << Temp1 << "\t\t  " << Temp2 << "\t" << Temp3 << endl;
			}	
		}
	}
	Input.close();
}
