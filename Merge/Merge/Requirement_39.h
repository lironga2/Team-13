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
	Input.open("Stock.txt");
	cout << "product cct\t"<<"  "<<"product name\tproduct amount" << endl;
	while (!Input.eof())
	{
		Input >> Product_Cct;
		if (!Input.eof())
		{
			Input >> Product_Name;
			Input >> The_Amount;
			Input >> The_Amount;
			Amount = ConvertToNum(The_Amount);
			cout << Product_Cct <<"\t\t  "<< Product_Name <<"\t"<< Amount << endl;
		}
	}
	Input.close();
}