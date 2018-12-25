#pragma once
#pragma once
#include"Requirements_1_to_3.h"
#include"Requirement_38.h"
#include"Requirement_39.h"
#include"Requirement_31.h"

using namespace std;

string Convert_To_String(int Amount);

void Add_Product_To_Stock()
{
	Install_Supllayer_Product();
	ifstream Input;
	ofstream Output;
	string Search;
	Product Product_To_Add;
	Product Product_In_Stock;
	int Product_Amount_To_Add;
	int Product_Amount_In_Stock;
	string The_Amount_To_Add;
	string The_Current_Amount;
	bool Flag = true;
	bool If_Cct_Supplayer = false;
	char User_Option;
	while (Flag)
	{
		Stock_Report();
		cout << endl;
		Stock_Shortage();
		cout << endl;
		//Print_Supllayer_Product();
		bool Exsist_Flag = false;
		//do
		//{
			cout << "Enter product cct: ";
			cin >> Product_To_Add.cct;
		//	for (int i = 0; i < SIZE; i++)
		//	{
		//		if (Product_To_Add.cct.compare(Supllayer[i].Product->cct) == 0)
		//		{
		//			If_Cct_Supplayer = true;
		//		}
		//	}
		//	if (!If_Cct_Supplayer)
		//	{
		//		cout << "Invalid cct.Try again." << endl;
		//	}
		//} while (!If_Cct_Supplayer);
		cout << "Enter product amount: ";
		cin >> Product_Amount_To_Add;
		Input.open("Stock.txt");
		Output.open("Temp.txt");
		while (!Input.eof())
		{
			Input >> Product_In_Stock.cct;
			if (!Input.eof())
			{
				Input >> Product_In_Stock.name;
				Input >> Product_In_Stock.price;
				Input >> The_Current_Amount;
				Product_Amount_In_Stock = ConvertToNum(The_Current_Amount);
				The_Amount_To_Add = Convert_To_String(Product_Amount_In_Stock + Product_Amount_To_Add);
				if (Product_In_Stock.cct.compare(Product_To_Add.cct) == 0)
				{
					int New_Amount = Product_Amount_In_Stock + Product_Amount_To_Add;
					if (New_Amount < 0)
					{
						New_Amount = 0;
						The_Amount_To_Add = "0#";
					}
					
					Output << Product_In_Stock.cct << ' ';
					Output << Product_In_Stock.name << ' ';
					Output << Product_In_Stock.price << ' ';
					Output << The_Amount_To_Add << endl;
					cout << "the current product amount: " << Product_Amount_In_Stock << endl;
					Exsist_Flag = true;
					cout << "successfully update the product : " << "cct: " << Product_In_Stock.cct << " name: " << Product_In_Stock.name << endl;
					cout << "New amount is: " << New_Amount << endl;
				}
				//else if ((Product_In_Stock.cct.compare(Product_To_Add.cct) == 0 && Product_In_Stock.name.compare(Product_To_Add.name) != 0))
				//{
				//	cout << "Product cct already exsist for: " << Product_In_Stock.name << endl;
				//	Exsist_Flag = true;
				//}
				//else if ((Product_In_Stock.cct.compare(Product_To_Add.cct) != 0 && Product_In_Stock.name.compare(Product_To_Add.name) == 0))
				//{
				//	cout << "Product name already exsist for: " << Product_In_Stock.cct << endl;
				//	Exsist_Flag = true;
				//}
				else
				{
					Output << Product_In_Stock.cct << ' ';
					Output << Product_In_Stock.name << ' ';
					Output << Product_In_Stock.price << ' ';
					Output << The_Current_Amount << endl;
				}
			}
		}
		Input.close();
		Output.close();
		if (!Exsist_Flag)
		{
			cout << "Enter product Name (ProductName): ";
			cin >> Product_To_Add.name;
			cout << "Enter product price: ";
			cin >> Product_To_Add.price;
			Output.open("Temp.txt", std::fstream::app);
			Output << Product_To_Add.cct << ' ';
			Output << Product_To_Add.name << ' ';
			Output << Product_To_Add.price << ' ';
			The_Amount_To_Add = Convert_To_String(Product_Amount_To_Add);
			Output << The_Amount_To_Add;
			Output.close();
			cout << "The new product: " << "cct: " << Product_To_Add.cct << " name: " << Product_To_Add.name << " price: " << Product_To_Add.price << " amount: " << Product_Amount_To_Add << endl << "successfully added to stock" << endl;
		}
		Input.open("Temp.txt");
		Output.open("Stock.txt");
		while (!Input.eof())
		{
			Input >> Product_In_Stock.cct;
			if (!Input.eof())
			{
				Input >> Product_In_Stock.name;
				Input >> Product_In_Stock.price;
				Input >> The_Current_Amount;
				Output << Product_In_Stock.cct << ' ';
				Output << Product_In_Stock.name << ' ';
				Output << Product_In_Stock.price << ' ';
				Output << The_Current_Amount << endl;

			}
		}
		Input.close();
		Output.close();
		cout << "Press if you want add another product press Y/y or any key to back" << endl;
		cin >> User_Option;
		if (User_Option != 'Y' && User_Option != 'y')
		{
			Flag = false;
		}
	}
}


string Convert_To_String(int Amount)
{
	char* String_Amount;
	int i = 1;
	int Number_Len = 0;
	int The_Number = Amount;
	while (The_Number)
	{
		Number_Len++;
		The_Number /= 10;
	}
	String_Amount = new char[Number_Len + 2];
	The_Number = Amount;
	String_Amount[Number_Len] = '#';
	String_Amount[Number_Len + 1] = '\0';
	while (The_Number)
	{
		String_Amount[Number_Len - i] = (The_Number % 10) + '0';
		i++;
		The_Number /= 10;
	}
	string Str = String_Amount;
	return Str;
}
bool isProductCctExist(string cct)
{
	ifstream Input;
	string transfer;
	Input.open("Stock.txt");
	if (Input)
	{
		Input >> transfer;
		while (!Input.eof())
		{
			if (transfer.compare(cct) == 0)
				return true;
			Input >> transfer;
		}
	}
	Input.close();
	return false;

}
void changeProductPrice()
{
	system("cls");
	string product_cct;
	ifstream Input;
	ofstream Output;
	string transfer;
	int price_to_change;
	bool flag = true;
	
	do
	{
		if (!flag)
			cout << "product not in stock, enter cct again" << endl;
		cout << "enter product cct that u want to change his price" << endl;
		cin >> product_cct;
		flag = false;
	}
		while (!isProductCctExist(product_cct));
	
	do
	{
		cout << "enter new price" << endl;
		cin >> price_to_change;
		if (price_to_change < 1)
		{
			cout << "price not valid, please try again" << endl;
		}
	} while (price_to_change < 1);

	cout << "Product price changed." << endl;
	Input.open("Stock.txt");
	Output.open("Temp.txt");
	if (Input)
	{
		Input >> transfer;
		while (!Input.eof())
		{
			if (product_cct.compare(transfer) == 0)
			{
				Output << transfer<< ' ';
				Input >> transfer;
				Output << transfer<< ' ';
				Input >> transfer;
				Output << price_to_change << ' ';
				Input >> transfer;
				Output << transfer << endl;
				Input >> transfer;
			}
			else
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