#pragma once
#include"Requirement_34.h"
#include"Requirement_38.h"
#include"Requirement_39.h"

void Remove_Product_From_Stock()
{
	Stock_Report();
	Stock_Shortage();
	ifstream Input;
	ofstream Output;
	string Cct_To_remove;
	string Amount;
	string transfer;
	Product Product;
	cout << "Enter Product cct: ";
	cin >> Cct_To_remove;
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
					cout << "Product has been removed from the stock" << endl;
					continue;
				}
				Output << Product.cct << ' ' << Product.name << ' ' << Product.price << ' ' << Amount << endl;
			}
		}
		Input.close();
		Output.close();
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
	else
	{
		cout << "Product isn't exists int the stock" << endl;
	}
}
