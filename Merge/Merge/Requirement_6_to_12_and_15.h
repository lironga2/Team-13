#pragma once
#include"Requirements_1_to_3.h"
#include "Requirements_5.h"
#include<stdlib.h>

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

void locateTransaction()
{
	string number_transaction;
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
			cout << "Number of transcation:" << number_transaction << endl;
			file_transaction >> transaction_to_compare;
			
			while ((transaction_to_compare[0] != '#') && (!file_transaction.eof()))
			{
				cout << transaction_to_compare<<' ';
				if (!(transaction_to_compare.compare("Total") == 0))
					cout << endl;
				file_transaction >> transaction_to_compare;
			}
		}
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
			if (flag) 
			{
				file_transaction >> number_transaction;
			}
			file_transaction >> date_to_compare;
			file_transaction >> id_to_compare;

			if ((date_to_compare.compare(today) == 0) && (id_to_compare.compare(worker_id) == 0))
			{
				cout << "Number of transcation: " << number_transaction << endl;
				file_transaction >> number_transaction;
				while ((number_transaction[0] != '#') && (!file_transaction.eof()))
				{
					if (number_transaction == "Total") 
					{
						cout << number_transaction;
						file_transaction >> number_transaction;
					}
					else if (number_transaction == "bill:")
					{
						cout << ' ' << number_transaction << endl;
						file_transaction >> temp;
						number_transaction = to_string(temp);
						sum_sales += temp;
						flag = false;
					}
					else
					{
						cout << number_transaction << endl;
						file_transaction >> number_transaction;
					}
				}
			}
			else 
				while ((number_transaction[0] != '#') && (!file_transaction.eof()))
				{
					file_transaction >> number_transaction;
					flag = false;
				}
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
void returnProduct() //needs to check what to do with original transaction, now it only increase the product +1 in stock.txt
					 //and not change sum
{
	string product_cct;
	locateTransaction();
	cout << "enter cct of product that you want to return" << endl;
	cin >> product_cct;
	deleteProductFromStock(product_cct);
	cout << "product hasz returned" << endl;
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
