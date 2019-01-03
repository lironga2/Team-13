#pragma once
#include"Requirements_1_to_3.h"
#include "Requirements_5.h"
//#include"Requirement_26.h"
#include<stdlib.h>
using namespace std;

int productInStock(string test ="NO")  //this function get input of cct from user, open stock file and check if its in stock
{
	string cct;
	ifstream Input;
	string Product_Name;
	string Product_Cct;
	string The_Amount;
	bool flag = true;
	if (test.compare("NO") == 0)
	{
		Input.open("Stock.txt");

		while (!Input.eof())
		{
			Input >> Product_Cct;
			if (!Input.eof())
			{
				Input >> Product_Name;
				Input >> The_Amount;
				Input >> The_Amount;
				if (flag)
				{
					cout << "Stock product table:" << endl;
					cout << "product cct\t" << "  " << "product name" << endl;
					cout << "----------------------------------------------" << endl;
					flag = false;
				}

				cout << Product_Cct << "\t\t  " << Product_Name << endl;
				cout << "----------------------------------------------" << endl;
			}
		}
		Input.close();
	}
	if (test.compare("NO") == 0)
	{
		cout << "Enter product cct" << endl;
		cin >> cct;
	}
	else 
		cct = test;
	if (validCct(cct)) //before open the file check if cct valid
	{
		ifstream Input;
		Input.open("Stock.txt");
		string Copy_String;
		while (!(Input.eof()))
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				if (cct.compare(Copy_String) == 0)
				{
					Input >> Copy_String;
					Input >> Copy_String;
					Input >> Copy_String;
					int Product_Amount;
					Product_Amount = ConvertToNum(Copy_String);
					if (Product_Amount > 0)
					{
						if (test.compare("NO") == 0)
						{
							system("cls");
							cout << "Product in stock , amount = :" << Product_Amount << endl;
						}
						else
						{
							Input.close();
							return 1;
						}
					}
					else
					{
						if (test.compare("NO") == 0)
						{
							system("cls");
							cout << "Product in stock, but amount is 0 " << endl;
						}
						else
						{
							Input.close();
							return 0;
						}
					}
				}
			}
		}
		Input.close();
	}
	else
	{
		if (test.compare("NO") == 0)
		{
			system("cls");
			cout << "Product not sell in the store" << endl;
		}
		return 0;
	}
	return 1;
}

string productPrice(string test_cct="NO")  //get input of cct from user and return his price
{
	string cct;
	fstream Stock;
	string file_cct;
	string product_name;
	string product_price;
	ifstream Input;
	string Product_Name;
	string Product_Cct;
	string The_Amount;
	bool flag = true;
	if (test_cct.compare("NO") == 0)
	{
		Input.open("Stock.txt");
		while (!Input.eof())
		{
			Input >> Product_Cct;
			if (!Input.eof())
			{
				Input >> Product_Name;
				Input >> The_Amount;
				Input >> The_Amount;
				if (flag)
				{
					cout << "Stock product table:" << endl;
					cout << "product cct\t" << "  " << "product name" << endl;
					cout << "----------------------------------------------" << endl;
					flag = false;
				}

				cout << Product_Cct << "\t\t  " << Product_Name << endl;
				cout << "----------------------------------------------" << endl;
			}
		}
		Input.close();
	}
	if (test_cct.compare("NO") == 0)
	{
		cout << "Enter product cct that u want to check his price" << endl;
		cin >> cct;
	}
	else
	{
		cct = test_cct;
	}
	if (validCct(cct))
	{
		Stock.open("Stock.txt");
		while (!Stock.eof())
		{
			Stock >> file_cct;
			if (file_cct.compare(cct) == 0)
			{
				Stock >> product_name >> product_price;
				if (test_cct.compare("NO") == 0)
				{
					system("cls");
					cout << product_name << "price is: " << product_price << endl;
				}
				Stock.close();
				return product_price;
			}
		}
		Stock.close();
	}
	else
	{
		if (test_cct.compare("NO") == 0)
		{
			system("cls");
			cout << "Product not in stock" << endl;
		}
		return "Product not in stock";
	}
}

string locateTransaction() //print transaction by input his number
{
	int Endl = 0; // counter to endl every 3 lines
	string number_transaction;
	bool transaction_exist=false;
	fstream file_transaction;
	string transaction_to_compare; //variable to save num of transaction and then to save other variable

	do {
		cout << "Enter number of transaction (in format #Number)" << endl;
		cin >> number_transaction;
	} while (number_transaction[0] != '#');
	file_transaction.open("Transaction.txt");
	while (!file_transaction.eof())
	{
		file_transaction >> transaction_to_compare;
		if (transaction_to_compare.compare(number_transaction) == 0)
		{
			transaction_exist = true;
			cout << "Number of transcation: " << number_transaction << endl;
			file_transaction >> transaction_to_compare;
			cout << "Date of transcation: " << transaction_to_compare << endl;
			file_transaction >> transaction_to_compare;
			cout << "Id of seller: " << transaction_to_compare << endl;
			cout << "Products: " << endl;
			file_transaction >> transaction_to_compare;
			while ((transaction_to_compare[0] != '#') && (!file_transaction.eof()))
			{
				cout << transaction_to_compare << ' ';
				Endl++;
				if (Endl % 3 == 0)
					cout << endl;
				file_transaction >> transaction_to_compare;
			}
			break;
		}
	}
		if (transaction_exist)
		{
			return number_transaction;
		}
		else
		{
			return "number_transaction didnt found!";
		}
}

void dailySalesReport(string worker_id) //return the sales of the connected user from today date
{
	string date_to_compare;
	fstream file_transaction;
	string id_to_compare;
	string number_transaction;
	double sum_sales=0.0;
	double temp=0.0;
	bool flag = true;
	string today;

	UpdateDate();
	today = currDate;

	file_transaction.open("Transaction.txt");
	if (file_transaction.is_open())
	{
		while (!file_transaction.eof())
		{
			file_transaction >> number_transaction;
			while ((number_transaction[0] != '#') &&(!file_transaction.eof()))
			{
				file_transaction >> number_transaction;
			}
			file_transaction >> date_to_compare;
			file_transaction >> id_to_compare;

			if ((date_to_compare.compare(today) == 0) && (id_to_compare.compare(worker_id) == 0))
			{
				flag = true;
				cout << "Number of transcation: " << number_transaction << endl;
				file_transaction >> number_transaction;
				int Endl = 0;
				while ((number_transaction[0] != '#') && (!file_transaction.eof()))
				{
					if (number_transaction == "Total") 
					{
						cout << number_transaction;
						file_transaction >> number_transaction;
					}
					if (number_transaction == "bill:")
					{
						cout << ' ' << number_transaction;
						file_transaction >> temp;
						number_transaction = to_string(temp);
						sum_sales += temp;
						flag = false;
						cout << number_transaction << endl;
					}
						if (flag)
						{
							cout << number_transaction << ' ';
							Endl++;
							if (Endl % 3 == 0)
							{
								cout << endl;
							}
							file_transaction >> number_transaction;
						}
						if (!flag)
						{
							break;
						}
				}
			}
		}
		file_transaction.close();
		cout << "Total profit of employee for today is: " << sum_sales << endl;
	}
}

void dailyClubMebmer(string worker_id) ////return the club members that add from the connected user of today
{
	string date_to_compare;
	fstream file_ClubMembers;
	string id_to_compare;
	int count_num_members = 0;
	string today;

	UpdateDate();
	today = currDate;

	file_ClubMembers.open("ClubMember.txt");
	if (file_ClubMembers.is_open())
	{
		while (!file_ClubMembers.eof())
		{
			file_ClubMembers >> date_to_compare;
			if (date_to_compare.compare(today) == 0)
			{
				file_ClubMembers >> id_to_compare;
				if (id_to_compare.compare(worker_id) == 0)
				{
					count_num_members++;
					date_to_compare = id_to_compare;
				}
			}
		}
	}
	cout << "Number of daily club members added: " << count_num_members << endl;
}
void returnProduct() //return product by reduce the amount of money from cashier , remove product from transaction and adding it back to stock 
{
	UpdateDate();
	string product_cct;
	string Transaction_Number = locateTransaction();
	if (Transaction_Number.compare("number_transaction didnt found!") == 0)
	{
		cout << "number_transaction didnt found!" << endl;
	}
	else
	{
		cout << "enter cct of product that you want to return" << endl;
		cin >> product_cct;
		deleteProductFromStock(product_cct);
		cout << "product has returned" << endl;
		ifstream Input;
		ofstream return_product;
		ofstream Output;
		string Transfer;
		bool Done_Flag = true;
		bool Flag = true;
		Input.open("Transaction.txt");
		return_product.open("ReturnProduct.txt" , std::fstream::app);
		Output.open("Temp.txt");
		int Endl = 0;
		double price;
		double TotalPrice = 0;
		while (!Input.eof())
		{
			Input >> Transfer;
			if (Transfer.compare(Transaction_Number) == 0)
			{
				while (!Transfer.compare("Total") == 0 && (!Input.eof()))
				{
					if (Transfer.compare(product_cct) == 0 && (Flag))
					{
						return_product << currDate << ' ' << Transfer << ' ';
						Input >> Transfer;
						return_product << Transfer << ' ';
						Input >> price;
						return_product << price << endl;
						Input >> Transfer;
						Flag = false;
					}
					else 
					{
						Output << Transfer << ' ';
						Input >> Transfer;
						Output << Transfer << ' ';
						Input >> Transfer;
						Output << Transfer << endl;
						Input >> Transfer;
					}
				}
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << ' ';
				Input >> TotalPrice;
				Output << TotalPrice - price << endl;
			}
			else 
			{
				while (!(Transfer.compare("Total") == 0) && (!Input.eof())) // output to file untill end of transaction
				{
					Output << Transfer << ' ';
					Input >> Transfer;
					Output << Transfer << ' ';
					Input >> Transfer;
					Output << Transfer << endl;
					Input >> Transfer;
				}
				if (!Input.eof())
				{
					Output << Transfer << ' ';
					Input >> Transfer;
					Output << Transfer << ' ';
					Input >> Transfer;
					Output << Transfer << endl;
				}
			}
		}
			Input.close();
			Output.close();
			return_product.close();
			Input.open("Temp.txt"); //output from temp to transaction to update the txt
			Output.open("Transaction.txt");
			while (!Input.eof())
			{
				Input >> Transfer;
				if (!Input.eof())
				{
					Output << Transfer << ' ';
					Endl++;
					if (Endl % 3 == 0)
						Output << endl;
				}
			}
		Input.close();
		Output.close();
	}

}

void saleNewGiftCard() //sales new giftcard and add it to giftcard txt with his amount and date of sell
{
	UpdateDate();
	string val;
	int giftcard_number=0;
	int giftcard_value = 0;
	char ch;
	do
	{
		cout << "Enter the value of the giftcard that u want to buy" << endl;
		cin >> val; //Change the type of the giftcard_value argument to string.
		giftcard_value = convertStringToNum(val);
		if (giftcard_value < 0)
		{
			cout << "The Value of giftcard invlaid try again" << endl;
		}
	} while (giftcard_value < 0);
	fstream file_giftcard;
	file_giftcard.open("GiftCard.txt");
	if (file_giftcard.is_open())
	{
		while (!file_giftcard.eof())
		{
			file_giftcard >> ch;
			if (ch == '#')
			{
				file_giftcard >> giftcard_number;
			}
		}
	}
	file_giftcard.close();
	giftcard_number += 1;
	file_giftcard.open("GiftCard.txt", std::fstream::app);
	if (file_giftcard.is_open())
	{
		file_giftcard << '#' << giftcard_number << ' ' << giftcard_value << ' ' << currDate << endl;
	}
	file_giftcard.close();
	cout << "gift card sold succeeded , your amount in giftcard is: " << giftcard_value <<"\nyour giftcard number is: " << giftcard_number <<  endl;
}

void dailyGeneralSalesReport() { //total sales of all employees by today date with sum of all sells
	string date_to_compare;
	string id;
	fstream file_transaction;
	string number_transaction;
	double sum_sales = 0.0;
	double temp = 0.0;
	bool flag = true;
	string today;

	UpdateDate();
	today = currDate;

	file_transaction.open("Transaction.txt");
	if (file_transaction.is_open())
	{
		while (!file_transaction.eof())
		{
			file_transaction >> number_transaction;
			while ((number_transaction[0] != '#') && (!file_transaction.eof()))
			{
				file_transaction >> number_transaction;
			}
			file_transaction >> date_to_compare;
			file_transaction >> id;

			if ((date_to_compare.compare(today) == 0))
			{
				flag = true;
				cout << "Number of transcation: " << number_transaction << endl;
				file_transaction >> number_transaction;
				int Endl = 0;
				while ((number_transaction[0] != '#') && (!file_transaction.eof()))
				{
					if (number_transaction == "Total")
					{
						cout << number_transaction;
						file_transaction >> number_transaction;
					}
					if (number_transaction == "bill:")
					{
						cout << ' ' << number_transaction;
						file_transaction >> temp;
						number_transaction = to_string(temp);
						sum_sales += temp;
						flag = false;
						cout << number_transaction << endl;
					}
					if (flag)
					{
						cout << number_transaction << ' ';
						Endl++;
						if (Endl % 3 == 0)
						{
							cout << endl;
						}
						file_transaction >> number_transaction;
					}
					if (!flag)
					{
						break;
					}
				}
			}
		}
		file_transaction.close();
		cout << "Total profit of all workers for today is: " << sum_sales << endl;
	}
}
void dailyReturnedProductReport() //generate report of daily return product
{
	UpdateDate();
	ifstream file_returned_product;
	string to_compare;
	bool Flag = false;
	file_returned_product.open("ReturnProduct.txt");
	file_returned_product >> to_compare;
	while (!file_returned_product.eof())
	{
		if (to_compare.compare(currDate) == 0 && !file_returned_product.eof())
		{
			if (!Flag) 
			{
				cout << "returend product today: " << endl;
				Flag = true;
			}
			
			file_returned_product >> to_compare;
			cout << to_compare << ' ';
			file_returned_product >> to_compare;
			cout << to_compare << ' ';
			file_returned_product >> to_compare;
			cout << to_compare << endl;
			file_returned_product >> to_compare;
		}
		file_returned_product >> to_compare;
	}
	file_returned_product.close();
}
