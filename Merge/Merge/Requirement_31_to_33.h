#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Requirements_5.h"
#include"Requirement_34.h"
//#include"Requirement_32.h"

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
	double Sum = 0;
};

void Install_Supplier_Product();
void Print_Supplier_Product();
void Create_New_Order();
void Add_Product_To_Order();
void Print_Order();
void Remove_Product_From_Order();
void Complete_Order();

static Order* Supplier;
static int Supplier_Product_Amount = 0;
static bool Install_Supplier_Product_Flag = true;

void Install_Supplier_Product()
{
	if (Install_Supplier_Product_Flag)
	{
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
		Supplier = new Order[Supplier_Product_Amount];
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
	cout << "product cct\t" << "  " << "product name\tproduct price/t" << endl;
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		cout << Supplier[i].Product->cct << "\t\t  " << Supplier[i].Product->name << "\t" << Supplier[i].Product->price << endl;
		cout << "----------------------------------------------" << endl;
	}
}

void Create_New_Order()
{
	system("cls");
	Install_Supplier_Product();
	string Option_Validation;
	int Option;
	bool Flag = true;
		while (Flag)
	{
		cout << "Press 1) to add product to order" << endl;
		cout << "Press 2) to remove product from order" << endl;
		cout << "Press 3) to complete the order" << endl;
		cout << "Press 4) to print the order" << endl;
		cin >> Option_Validation;
		Option = convertStringToNum(Option_Validation);

		switch (Option)
		{
			case 1:
			{
				system("cls");
				Print_Supplier_Product();
				Add_Product_To_Order();
				break;
			}
			case 2:
			{
				system("cls");
				Print_Order();
				Remove_Product_From_Order();
				break;
			}
			case 3:
			{
				system("cls");
				Complete_Order();
				Flag = false;
				break;
			}
			case 4:
			{
				system("cls");
				Print_Order();
				break;
			}
			case 0:
			{
				system("cls");
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

void Add_Product_To_Order()
{
	string Cct;
	char Option;
	bool Flag = false;
	bool Try_Againe = true;
	while (Try_Againe)
	{
		cout << "Enter product to: ";
		cin >> Cct;
		for (int i = 0; i < Supplier_Product_Amount; i++)
		{
			if (Supplier[i].Product->cct.compare(Cct) == 0)
			{
				Supplier[i].Product->amount++;
				Supplier->Sum += Supplier[i].Product->price;
				Flag = true;
				Try_Againe = false;
			}
		}
		if (Flag)
		{
			system("cls");
			cout << "Product successfully added" << endl;
		}
		else
		{
			system("cls");
			cout << "Product cct:"<< Cct <<" Invalid " << endl;
			cout << "if you want try again press Y|y else press any key to continue" << endl;
			cin >> Option;
			if (Option != 'Y' && Option != 'y')
			{
				Try_Againe = false;
			}
		}
	}
}

void Remove_Product_From_Order()
{
	string Cct;
	char Option;
	bool Flag = false;
	bool Try_Againe = true;
	bool Amount_Flag = true;
	while (Try_Againe)
	{
		system("cls");
		Print_Order();
		cout << "Enter product to: ";
		cin >> Cct;
		for (int i = 0; i < Supplier_Product_Amount; i++)
		{
			if (Supplier[i].Product->cct.compare(Cct) == 0)
			{
				if (Supplier[i].Product->amount > 0)
				{
					Supplier[i].Product->amount--;
					Supplier->Sum -= Supplier[i].Product->price;
					Flag = true;
					Try_Againe = false;
				}
				else
				{
					Amount_Flag = false;
				}
			}
		}
		if (Flag)
		{
			system("cls");
			cout << "Product successfully removed" << endl;
		}
		//else if (!Amount_Flag)
		//{
		//	system("cls");
		//	cout << "Product amount alredy 0 cant remove" << endl;
		//}
		else
		{
			system("cls");
			cout << "Product cct:" << Cct << " Invalid " << endl;
			cout << "if you want try again press Y|y else press any key to continue" << endl;
			cin >> Option;
			if (Option != 'Y' && Option != 'y')
			{
				Try_Againe = false;
			}
		}
	}
}

void Print_Order()
{
	bool Flag = true;
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		if (Supplier[i].Product->amount > 0)
		{
			if (Flag)
			{
				system("cls");
				cout << "product cct\t" << "  " << "product name\tproduct price" << endl;
				Flag = false;
			}
			cout << Supplier[i].Product->cct << "\t\t  " << Supplier[i].Product->name << "\t" << Supplier[i].Product->price <<"\t"<< Supplier[i].Product->amount << endl;
			cout << "----------------------------------------------" << endl;
		}
	}
	if (Flag)
	{
		cout << "The order is empty" << endl;
	}
	else
	{
		cout << "Total order price: " << Supplier->Sum << endl;
		cout << "----------------------------------------------" << endl;
	}
}

void Complete_Order()
{
	ifstream Input;
	ofstream Output;
	double CashBox;
	string Transfer;
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
				//CashBox -= Supplier->Sum;
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
				double Current_Money;
				Input >> Current_Money;
				Current_Money += Supplier->Sum;
				Output << Current_Money << endl;
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
	Input.open("Stock.txt");
	Output.open("Temp.txt");
	The_Product Temp_Product;
	bool Flag = true;
	int k = 0;
	int* arr = new int[Supplier_Product_Amount];
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		arr[i] = -1;
	}
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		if (Supplier[i].Product->amount > 0)
		{
			arr[i] = i;
		}
	}
	while (!Input.eof())
	{
		Input >> Temp_Product.cct;
		if (!Input.eof())
		{
			Input >> Temp_Product.name;
			Input >> Temp_Product.price;
			string Temp;
			Input >> Temp;
			Temp_Product.amount = ConvertToNum(Temp);
			for (int i = 0; i < Supplier_Product_Amount; i++)
			{
				if (Temp_Product.cct.compare(Supplier[i].Product->cct) == 0 && Supplier[i].Product->amount > 0)
				{
					Output << Temp_Product.cct << ' ';
					Output << Temp_Product.name << ' ';
					Output << Temp_Product.price << ' ';
					int Temp_Amount = Temp_Product.amount + Supplier[i].Product->amount;
					Temp = Convert_To_String(Temp_Amount);
					Output << Temp << endl;
					arr[i] =-1;
					Flag = false;
				}
			}
			if (Flag)
			{
				Output << Temp_Product.cct << ' ';
				Output << Temp_Product.name << ' ';
				Output << Temp_Product.price << ' ';
				Output << Temp << endl;
			}
		}
	}
	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		if (arr[i] != -1)
		{
			string Temp;
			Output << Supplier[i].Product->cct << ' ';
			Output << Supplier[i].Product->name << ' ';
			double New_Price = Supplier[i].Product->price * 2;
			Output << New_Price << ' ';
			Temp = Convert_To_String(Supplier[i].Product->amount);
			Output << Temp << endl;
		}
	}
	Input.close();
	Output.close();

	Input.open("Temp.txt");
	Output.open("Stock.txt");
	while (!Input.eof())
	{
		Input >> Temp_Product.cct;
		if (!Input.eof())
		{
			string Temp;
			Input >> Temp_Product.name;
			Input >> Temp_Product.price;
			Input >> Temp;
			Output << Temp_Product.cct << ' ';
			Output << Temp_Product.name << ' ';
			Output << Temp_Product.price << ' ';
			Output << Temp << endl;

		}
	}
	Input.close();
	Output.close();
	Input.open("Orders.txt");
	int Order_Number = 1;
	while (!Input.eof())
	{
		string Temp;
		Input >> Temp;
		if (!Input.eof())
		{
			if (Temp[0] == '#')
			{
				Order_Number++;
			}
		}
	}
	Input.close();
	UpdateDate();
	Output.open("Orders.txt", std::fstream::app);
	{
		Output << '#' << Order_Number << ' ' << currDate << endl;
		for (int i = 0; i < Supplier_Product_Amount; i++)
		{
			if (Supplier[i].Product->amount > 0)
			{
				Output << Supplier[i].Product->cct << ' ';
				Output << Supplier[i].Product->name << ' ';
				Output << Supplier[i].Product->price << ' ';
				Output << Supplier[i].Product->amount << endl;
			}
		}
		Output << "Total payment:" << ' '<< Supplier->Sum << endl;
	}
	Output.close();

	for (int i = 0; i < Supplier_Product_Amount; i++)
	{
		Supplier[i].Product->amount = 0;
	}
	Supplier->Sum = 0;
}