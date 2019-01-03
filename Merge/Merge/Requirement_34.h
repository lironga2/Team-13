#pragma once
#pragma once
#include"Requirements_1_to_3.h"
#include"Requirement_38.h"
#include"Requirement_39.h"
//#include"Requirement_31.h"

using namespace std;

string Convert_To_String(int Amount);

string Add_Product_To_Stock(string test_cct="NO",int test_amount=0)
{
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
	bool Exsist_Flag = false;
	while (Flag)
	{
		Exsist_Flag = false;
		if (test_cct.compare("NO") == 0)
		{
			Stock_Report();
			cout << endl;
			Stock_Shortage();
			cout << endl;
			cout << "Enter product cct: ";
			cin >> Product_To_Add.cct;
			cout << "Enter product amount: ";
			cin >> Product_Amount_To_Add;
		}
		else
		{
			Product_To_Add.cct = test_cct;
			Product_Amount_To_Add = test_amount;
		}
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
					if (test_cct.compare("NO") == 0)
					{
						cout << "the current product amount: " << Product_Amount_In_Stock << endl;
					}
					Exsist_Flag = true;
					if (test_cct.compare("NO") == 0)
					{
						cout << "successfully update the product : " << "cct: " << Product_In_Stock.cct << " name: " << Product_In_Stock.name << endl;
						cout << "New amount is: " << New_Amount << endl;
					}
				}
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
			if (test_cct.compare("NO") != 0)
			{
				return"Failed";
			}
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
		if (test_cct.compare("NO") != 0)
		{
			Flag = false;
		}
		if (test_cct.compare("NO") == 0)
		{
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
	if (Exsist_Flag && !Flag)
	{
		return "product amount successfully added";
	}
	else if (!Exsist_Flag && !Flag)
	{
		return"new product amount successfully added";
	}
}


string Convert_To_String(int Amount) //convert int to string and paste # to end of string
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
bool isProductCctExist(string cct) //check if cct exist in stock without checking if enough amount of products
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
void changeProductPrice() //change the product price to whatever the procurement_manager wants
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