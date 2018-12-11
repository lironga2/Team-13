#pragma once
#include"Requirements_1_to_3.h"

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
			
			while (transaction_to_compare[0] != '#')
			{
				cout << transaction_to_compare << endl;
				file_transaction >> transaction_to_compare;
			}
		}
	}
}