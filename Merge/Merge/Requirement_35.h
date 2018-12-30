#pragma once
#include"Requirement_34.h"
#include"Requirement_38.h"
#include"Requirement_39.h"

string Remove_Product_From_Stock(string test_cct ="NO")
{
	if (test_cct.compare("NO") == 0)
	{
		Stock_Report();
	}
	//Stock_Shortage();
	ifstream Input;
	ofstream Output;
	string Cct_To_remove;
	string Amount;
	string transfer;
	Product Product;
	if(test_cct.compare("NO") == 0)
	{
	cout << "Enter Product cct: ";
	cin >> Cct_To_remove;
	}
	else
	{
		Cct_To_remove = test_cct;
	}
	Input.open("Stock.txt");
	Output.open("Temp.txt");
	if (isProductCctExist(Cct_To_remove))
	{
		while (!Input.eof())
		{
			Input >> Product.cct;
			if (!Input.eof())
			{
				Input >> Product.name;
				Input >> Product.price;
				Input >> Amount;
				if (Product.cct.compare(Cct_To_remove) == 0)
				{
					if (test_cct.compare("NO") == 0)
					{
						cout << "Product has been removed from the stock" << endl;
					}
					Output << Product.cct << ' ' << Product.name << ' ' << Product.price << ' ' << "0#" << endl;
					continue;
				}
				Output << Product.cct << ' ' << Product.name << ' ' << Product.price << ' ' << Amount << endl;
			}
		}
		Input.close();
		Output.close();
		if (test_cct.compare("NO") == 0)
		{
			Output.open("Stock.txt");
			Input.open("Temp.txt");
			if (Input)
			{
				Input >> transfer;
				while (!Input.eof())
				{
					Output << transfer << ' ';
					Input >> transfer;
					Output << transfer << ' ';
					Input >> transfer;
					Output << transfer << ' ';
					Input >> transfer;
					Output << transfer << endl;
					Input >> transfer;
				}
			}
			Input.close();
			Output.close();
		}
	}
	else
	{
		if (test_cct.compare("NO") == 0)
		{
			cout << "Product isn't exists int the stock" << endl;
		}
			return "Product isn't exists int the stock";
	}
	return "Product has been removed from the stock";

}
