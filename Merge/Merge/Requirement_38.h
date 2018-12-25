#pragma once
#include<string>
#include<fstream>
#include"Requirements_1_to_3.h"
void Stock_Shortage()
{
	ifstream Input;
	string Product_Name;
	string Product_Cct;
	string The_Amount;
	bool Amount, flag = true;
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
			if (Amount == 0) {
				if (flag) {
					cout << "Shortage table:" << endl;
					cout << "product cct\t" << "  " << "product name" << endl;
					cout << "------------------------------" << endl;
					flag = false;
				}
				cout << Product_Cct << "\t\t  " << Product_Name << endl;
				cout << "------------------------------" << endl;
			}
		}
	}
	if (flag)
	{
		cout << "there are no shortages in stock" << endl;
	}
	Input.close();
}