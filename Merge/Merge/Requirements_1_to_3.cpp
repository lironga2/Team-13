#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Requirements_1_to_3.h"
#include <time.h>
using namespace std;

static char todaydate[30];
time_t l = time(NULL);
struct tm lm = *localtime(&l);

void newBill(Bill** bill);
void newProduct(Product** product);
void creatBill(string id);
void addProductToBill(Bill** bill);
bool validCct(string product_cct);
void updateBill(Bill*** bill,string product_cct);
void deleteExistProduct(Bill ** bill);
void makePayment(Bill *bill);
bool findFriendClub();



void newBill(Bill** bill) {
	*bill = new Bill;
	if (!bill) {
		cout << "Bad allocate." << endl;
		exit(1);
	}

	invoice_number++;
}

void newProduct(Product** product) {
	*product = new Product;
	if (!product) {
		cout << "Bad allocate." << endl;
		exit(1);
	}
}

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill(string id)
{
	lm.tm_mday += 1;
	lm.tm_year += 1900;
	sprintf(todaydate, "%d.%d.%d", lm.tm_mday, lm.tm_mon , lm.tm_year);
	cout << todaydate << endl;
	Bill *bill;
	newBill(&bill);
	bill->current_account_number = invoice_number;
	bool flag = true;
	char user_choise;
	bill->id = id;
	// לא לשכוח לבדוק תקינות קלט ולהוסיף הודעת שגיאה במקרה והקלט לא תקין
	do {
		cout << "1) Add a new product:" << endl;
		cout << "2) Delete an existing product:" << endl;
		cout << "3) Making a payment:" << endl;
		cout << "4) Back:" << endl;
		cin >> user_choise;
		switch (user_choise)
		{
		case '1':
				addProductToBill(&bill);
				break;
		case '2':
				deleteExistProduct(&bill);
				break;
		case '3': // לשחרר מערך מוצרים של החשבון הנוכחי תרשום שנדע מה
				makePayment(bill);
				flag = false;
			break;
		case '4': // לא לשכוח שחרור הקצאה לחשבון החדש וגם לעשות -- למספר חשבון הגלובאלי
				  // לשנות דגל לשלילי ולמחוק כל מה שקיים בקובץ החשבון הנוכחי
					flag = false;
					break;
		default:
			cout << "Invalid choice. Try again." << endl;
			break;
		}
	} while (flag);
}

void addProductToBill(Bill** bill)
{
	string product_cct;
	do {
		cout << "Please Enter Product cct:" << endl; //cct -> makat.
		cin >> product_cct;
		if (!validCct(product_cct)) {
			cout << "Invalid cct.Try again." << endl;
		}
	} while (!validCct(product_cct));
	// if the cct is valid.
	cout << "Product successfully added" << endl;
	updateBill(&bill,product_cct);

}
// A function that checks if the cct that entered in a function addProductToBill() exists in the database.
bool validCct(string product_cct) {
	fstream Stock;
	string file_cct;
	Stock.open("Stock.txt");
	while (!Stock.eof())
	{
		Stock >> file_cct;
		if (file_cct.compare(product_cct) == 0)
		{
			return true;
		}
	}
	Stock.close();
	return false;
}

void updateBill(Bill*** bill,string product_cct) {
	// משיכת מחיר מהקובץ של המוצר של מספר המקט שהוזן למשתנה price

	ifstream Stock;
	Stock.open("Stock.txt");
	string name;
	string cct;
	double price = 0;
	while (!Stock.eof())
	{
		Stock >> cct;
		if (product_cct.compare(cct) == 0)
		{
			Stock >> name;
			Stock >> price;
			break;
		}
	}
	// משיכת הנתונים מהקובץ
	(*(*bill))->sum += price;
	int old_size = (*(*bill))->num_of_product;
	(*(*bill))->num_of_product++;
	int temp = (*(*bill))->num_of_product;
	if ((*(*bill))->num_of_product == 1)
	{
		(*(*bill))->product = new Product*;
		(*(*bill))->product[0] = new Product;
		(*(*bill))->product[0]->cct = cct;
		(*(*bill))->product[0]->name = name;
		(*(*bill))->product[0]->price = price;
	}
	else
	{
		Product** Assist = new Product *[temp];
		for (int i = 0; i < old_size; i++)
		{
			Assist[i] = new Product;
			Assist[i] = (*(*bill))->product[i];
		}
		Assist[old_size] = new Product;
		Assist[old_size]->cct = cct;
		Assist[old_size]->name = name;
		Assist[old_size]->price = price;
		delete((*(*bill))->product);
		(*(*bill))->product = Assist;
		Assist = nullptr;
	}

}

void deleteExistProduct(Bill ** bill)
{
	int index_to_delete = -1;
	bool flag = false; 
	if ((*(bill))->num_of_product == 0) 
	{
		cout << "The cart is empty." << endl;
	}
	else
	{
		string product_cct;
		cout << "Enter cct to delete product" << endl;
		cin >> product_cct;

		for(int i=0; i<(*(bill))->num_of_product; i++)
		{
			if (product_cct.compare((*(bill))->product[i]->cct) == 0 ) {
				index_to_delete = i;
			}
		}
		if (index_to_delete == -1)
		{
			cout << "The product does not exist in the cart" << endl;
		}
		else
		{
			Product** Assist = new Product* [(*(bill))->num_of_product - 1];
			int j = 0;
			for (int i = 0; i < (*(bill))->num_of_product; i++)
			{
				if (i = index_to_delete)
				{
					continue;
				}
				Assist[j] = new Product;
				Assist[j++] = (*bill)->product[i];
			}
			delete((*bill)->product);
			(*bill)->product = Assist;
			(*(bill))->num_of_product--;
			(*(bill))->sum -= (*bill)->product[index_to_delete]->price;
			Assist = nullptr;
			cout << "product has deleted" << endl;
		}
	}

	//לא לשכוח להוסיף את המוצר חזרה למלאי

}

void makePayment(Bill * bill)
{
	if(bill->num_of_product == 0)
	{
		cout << "There is no products in the bill" << endl;
		//exit(1); need back to bill menu.
	}
	else
	{
		char payment_type;
		long double cash = 0;
		string card_number;
		int month;
		int year;
		int CVV = 0;
		bool friend_club = false;
		char user_freind_club_choice;
		bool flag = true;
		bool validFlag = true;
		fstream transaction;
		char ch;

		cout << "Is the client a club member? 1) Yes 2)No" << endl;
		cin >> user_freind_club_choice;
		do {
			if (user_freind_club_choice == 1)
				if (findFriendClub()) {
					friend_club = true;
					bill->sum *= 0.95;
				}
				else
				{
					cout << "friend member dose not found. do you want try again? 1) Yes 2)No" << endl;
					cin >> user_freind_club_choice;
				}
		} while (user_freind_club_choice == 1);

		cout << "The products are:" << endl;
		for (int i = 0; i < bill->num_of_product; i++)
		{
			cout << bill->product[i]->name << ' - ' << bill->product[i]->price << endl;
		}

		cout << "Amount to pay: " << bill->sum;
		if (friend_club = true)
			cout << "You saved 5%! " << endl;
		do
		{
			cout << "How do you want to pay?: " << bill->sum;
			cout << "1) Cash 2)Credit Card: " << endl;
			cin >> payment_type;
			switch (payment_type)
			{
			case '1':
				cout << "How much money did you receive from the client?: " << endl;
				cin >> cash;
				cout << "Money return: " << cash - (bill->sum);
				flag = false;
				break;
			case '2': 
				do
				{
					if (!flag)
					{
						cout << "card number invalid" << endl;
					}

					cout << "card number" << endl;
					std::getline(std::cin, card_number);
					cout << card_number.length() << endl;
					if (card_number.length() != 8 || card_number.length() != 16)
					{
						flag = false;
					}
				} while (card_number.length() != 8 || card_number.length() != 16);
				validFlag = true;
				do
				{
					if (!flag)
					{
						cout << "validity invalid" << endl;
					}
					cout << "Enter validity: " << endl;
					cin >> month >> ch >> year;
					if (year < lm.tm_year +1900)
					{
						flag = false;
					}
					else
					{
						if ((year == lm.tm_year + 1900) && (month < lm.tm_mon + 1))
						{
							flag = false;
						}
					}
				} while ((year == lm.tm_year + 1900) && (month < lm.tm_mon + 1) || (year < lm.tm_year + 1900));
				validFlag = true;
				do
				{
					if (!flag)
					{
						cout << "CVV: " << endl;
					}
					cout << "Enter CVV: " << endl;
					cin >> CVV;
					if(CVV<0 || CVV > 999)
					{
						flag = false;
					}
				} while (CVV < 0 || CVV > 999);
				flag = false;
				break;
			default:
				cout << "Bad choice. Try again." << endl;
				break;
			}
		} while (flag);
		transaction.open("Transaction.txt", std::fstream::app);
		transaction << todaydate << ' ' << bill->id << ' ';
		transaction << "The products are:" << endl;
		for (int i = 0; i < bill->num_of_product; i++)
		{
			transaction << bill->product[i]->name << ' - ' << bill->product[i]->price << endl;
		}
		transaction << "Total bill: " << bill->sum << endl;
	}
}

bool findFriendClub() {
	string phone_number;
	cout << "Enter customer's phone number: " << endl;
	cin >> phone_number;
	string member_phone;
	ifstream ClubMember;
	ClubMember.open("ClubMember.txt");
	while (!ClubMember.eof())
	{
		ClubMember >> member_phone;
		if (phone_number.compare(member_phone) == 0)
		{
			ClubMember.close();
			return true;
		}
	}
	ClubMember.close();
	return false;
}
