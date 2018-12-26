#pragma once
#include<iostream>
#include<fstream>
#include<string>

#define SIZE 6

using namespace std;

typedef struct The_Product 
{
	string name;
	string cct;
	double price = 0;
	int amount = 0;
};

typedef struct Order 
{
	The_Product* Product;
};

static Order* Supplier;
static int Supplier_Product_Amount = 0;
static bool Install_Supplier_Product_Flag = true;

void Install_Supplier_Product()
{
	if (Install_Supplier_Product_Flag)
	{
		Supplier = new Order[SIZE];
		ifstream Input;
		string transfer;
		Input.open("Supplier.txt");
		while (!Input.eof())
		{
			Input >> transfer;
			if (!Input.eof())
			{
				if (transfer[0] == '#')
				{
					Supplier_Product_Amount++;
				}
			}
		}
		Input.close();
		for (int i = 0; i < Supplier_Product_Amount; i++)
		{
			Supplier[i].Product = new The_Product;
		}
		Input.open("Supplier.txt");
		while (!Input.eof())
		{
			Input >> transfer;
			for (int i = 0; i < Supplier_Product_Amount; i++)
			{
				if (!Input.eof())
				{
					Input >> Supplier[i].Product->cct;
					Input >> Supplier[i].Product->name;
					Input >> Supplier[i].Product->price;
					Input >> transfer;
				}
			}
		}
		Input.close();
		Install_Supplier_Product_Flag = false;
	}

}

void Print_Supplier_Product()
{
	cout << "Supplier product table:" << endl;
	cout << "product cct\t" << "  " << "product name\tproduct price" << endl;
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		cout << Supplier[i].Product->cct << "\t\t  " << Supplier[i].Product->name << "\t" << Supplier[i].Product->price << endl;
		cout << "----------------------------------------------" << endl;
	}
}

void Create_New_Order()
{
	Install_Supplier_Product();
	char Option;
	bool Flag = true;
	while (Flag)
	{
		cout << "Press 1) to add product to order" << endl;
		cout << "Press 2) to remove product from order" << endl;
		cout << "Press 3) to complete the order" << endl;
		switch (Option)
		{
			case '1':
			{
				system("cls");
				Print_Supplier_Product();
				//Add_Product_To_Order();
				break;
			}
			case '2':
			{
				system("cls");
				//Print_Order();
				//Remove_Product_From_Order();
				break;
			}
			case '3':
			{
				system("cls");
				//Complete_Order();
				Flag = false;
				break;
			}
			default:
			{
				cout << "Invalid option" << endl;
				break;
			}
		}
	}

}

void 