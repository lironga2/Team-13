#pragma once
#include<iostream>
#include"Requirements_1_to_3.h"
//#include"Requirement_26.h"

using namespace std;

void giveCleintDiscount(Bill** bill);

void giveCleintDiscount(Bill** bill)
{
	double Discount;
	double Deal_Price = 1;
	bool flag = false;
	do
	{
		if (flag)
		{
			cout << "Discount isn't valid" << endl;
		}
		cout << "Enter discount between 1% -> 25%: ";
		cin >> Discount;
		if (!(Discount >= 1 && Discount <= 25))
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	} while (flag);
	Deal_Price -= (Discount/100);
	(*bill)->sum = 0;
	for (int i = 0; i < (*bill)->num_of_product; i++)
	{
		(*bill)->product[i]->price *= Deal_Price;
		(*bill)->sum += (*bill)->product[i]->price;
	}
	system("cls");
	cout << "Discount of: " << Discount << "% was given to client successfully" << endl;
}
