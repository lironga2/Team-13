#pragma once
#include<iostream>
using namespace std;

typedef struct 
{
	double sum = 0;
	int num_of_product = 0;
}Bill;

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill()
{
	char user_choise;
	cout << "1) Add a new product:" << endl;
	cout << "2) Delete an existing product:" << endl;
	cout << "3) Making a payment:" << endl;
	cout << "4) Back:" << endl;
	// לא לשכוח לבדוק תקינות קלט ולהוסיף הודעת שגיאה במקרה והקלט לא תקין
	switch (user_choise)
	{
	case '1':
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	default:
		break;
	}
}

void addProductToBill()
{	
	int product_cct = 0;
	cout << "Please Enter Product cct:" << endl; //cct -> makat.
	cin >> product_cct;
	if (validCct) //The cct exist.
	{

	}
	
	

}

// A function that checks if the cct that entered in a function addProductToBill() exists in the database.
bool validCct(int product_cct) {
	// ריצה על מאגר המקטים ובדיקה אם המקט קיים
	return true;
		return false;
}
	