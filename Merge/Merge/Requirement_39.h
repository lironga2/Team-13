#pragma once
#include<string>
#include<fstream>
#include"Requirements_1_to_3.h"

using namespace std;

void Stock_Report()
{
	ifstream Input;
	string Product_Name;
	string Product_Cct;
	string The_Amount;
	int Amount;
	bool flag = true;
	Input.open("Stock.txt");

	while (!Input.eof())
	{
		Input >> Product_Cct;
		if (!Input.eof())
		{
			Input >> Product_Name;
			Input >> The_Amount;
			Input >> The_Amount;
			Amount = ConvertToNum(The_Amount);
			if (Amount)
			{
				if (flag)
				{
					cout << "Stock product table:" << endl;
					cout << "product cct\t" << "  " << "product name\tproduct amount" << endl;
					cout << "----------------------------------------------" << endl;
					flag = false;
				}

				cout << Product_Cct << "\t\t  " << Product_Name << "\t" << Amount << endl;
				cout << "----------------------------------------------" << endl;
			}
		}
	}
	if (flag)
	{
		cout << "there are no products in stock" << endl;
	}
	Input.close();
}