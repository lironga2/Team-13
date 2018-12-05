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
}