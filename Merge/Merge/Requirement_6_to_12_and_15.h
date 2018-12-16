#pragma once
#include"Requirements_1_to_3.h"
#include "Requirements_5.h"
#include<stdlib.h>
using namespace std;

void productInStock()
{
	string cct;
	cout << "Enter product cct" << endl;
	cin >> cct;
	if (validCct(cct))
	{
		cout << "Product in stock" << endl;
	}
	else
		cout << " Product not in stock" << endl;
}

void productPrice() 
{
	string cct;
	fstream Stock;
	string file_cct;
	string product_name;
	string product_price;
	cout << "Enter product cct that u want to check his price" << endl;
	cin >> cct;
	if (validCct(cct))
	{
		Stock.open("Stock.txt");
		while (!Stock.eof())
		{
			Stock >> file_cct;
			if (file_cct.compare(cct) == 0)
			{
				Stock >> product_name >> product_price;
				cout << product_name << "price is: " << product_price << endl;
			}
		}
		Stock.close();
	}
	else
		cout << "Product not in stock" << endl;
}

string locateTransaction()
{
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
			cout << "Number of transcation:" << number_transaction << endl;
			file_transaction >> transaction_to_compare;

			while ((transaction_to_compare[0] != '#') && (!file_transaction.eof()))
			{
				cout << transaction_to_compare << ' ';
				if (!(transaction_to_compare.compare("Total") == 0))
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

void dailySalesReport(string worker_id) 
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
			//else 
				//while ((number_transaction[0] != '#') && (!file_transaction.eof()))
				//{
				//	if (number_transaction[0] != '#')
				//	{
				//		file_transaction >> number_transaction;
				//	}
				//	flag = false;
				//}
		}
		file_transaction.close();
		cout << "Total profit of employee for today is: " << sum_sales << endl;
	}
}

void dailyClubMebmer(string worker_id)
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
void returnProduct() 
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
		bool boolflag = true;
		bool Flag = true;
		Input.open("Transaction.txt");
		return_product.open("ReturnProduct.txt" , std::fstream::app);
		Output.open("Temp.txt");
		int Endl = 0;
		double price;
		double TotalPrice = 0;
		while (!Input.eof())
		{
			if (boolflag)
			Input >> Transfer;
			if (Transfer.compare(Transaction_Number) == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					Output << Transfer << ' ';
					Input >> Transfer;
				}
				Output << endl;
				boolflag = true;
				if (Transfer.compare(product_cct) == 0 && (Flag))
				{
					return_product << currDate << ' ' << Transfer << ' ';
					Input >> Transfer;
					return_product << Transfer << ' ';
					Input >> price;
					return_product << price << endl;
					while (Transfer.compare("bill:") != 0)
					{
						Input >> Transfer;
						if (Transfer.compare("Total") == 0)
							Output << endl;
						Output << Transfer << ' ';
					}
					Input >> TotalPrice;
					Output << TotalPrice - price << endl;
					Flag = false;
					boolflag = true;
				}
			}
			else 
			{
				while (!(Transfer.compare(Transaction_Number) == 0) && (!Input.eof()))
				{
					for (int i = 0; i < 3; i++)
					{
						Output << Transfer << ' ';
						Input >> Transfer;
					}
					Output << endl;
					boolflag = false;
				}
			}
		}
	Input.close();
	Output.close();
	return_product.close();
	Input.open("Temp.txt");
	Output.open("Transaction.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
		Output << Transfer <<' ';
		Endl++;
		if (Endl % 3 == 0)
			Output << endl;
	}
	}

}

void saleNewGiftCard()
{
	int giftcard_number=0;
	int giftcard_value = 0;
	char ch;
	cout << "Enter the value of the giftcard that u want to buy" << endl;
	cin >> giftcard_value;
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
		file_giftcard << '#' << giftcard_number << ' ' << giftcard_value << endl;
	}
	file_giftcard.close();
	cout << "gift card sold succeeded , your amount in giftcard is: " << giftcard_value <<"\nyour giftcard number is: " << giftcard_number <<  endl;
}
