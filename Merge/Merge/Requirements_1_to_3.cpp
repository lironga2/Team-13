#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Requirements_1_to_3.h"
#include <time.h>
#include<stdlib.h>
using namespace std;

static char todaydate[30];
time_t l = time(NULL);
struct tm lm = *localtime(&l);
static bool Date_Flag = true;

void newBill(Bill** bill);
void newProduct(Product** product);
void creatBill(string id);
void addProductToBill(Bill** bill);
bool validCct(string product_cct);
void updateBill(Bill*** bill,string product_cct);
void deleteExistProduct(Bill ** bill);
void makePayment(Bill *bill);
bool findFriendClub();
int ConvertToNum(string Number);
void deleteProductFromStock(string product_cct);



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
	if(Date_Flag)
	{
		lm.tm_mon += 1;
		lm.tm_year += 1900;
		Date_Flag = false;
	}

	sprintf(todaydate, "%d.%d.%d", lm.tm_mday, lm.tm_mon , lm.tm_year);
	cout << todaydate << endl;
	Bill *bill;
	newBill(&bill);
	int Transaction_Number = 0;
	char ch = '0';
	ifstream Transaction;
	Transaction.open("Transaction.txt");
	if (Transaction.is_open())
	{
		while (!Transaction.eof())
		{
			Transaction >> ch;
			if (ch == '#')
			{
				Transaction >> Transaction_Number;
			}
		}
	}
	Transaction.close();
	invoice_number = Transaction_Number + 1;
	bill->current_account_number = invoice_number;
	bool flag = true;
	char user_choise;
	bill->id = id;
	// לא לשכוח לבדוק תקינות קלט ולהוסיף הודעת שגיאה במקרה והקלט לא תקין
	do {
		if (bill->num_of_product)
		{
			cout << "The products are:" << endl;
			for (int i = 0; i < bill->num_of_product; i++)
			{
				cout << bill->product[i]->name << " - " << bill->product[i]->price << endl;
			}
			cout << "Amount to pay: " << bill->sum << endl;
		}
		else
		{
			cout << "There is no products in the bill" << endl;
		}


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
	int toSend;
	string product_cct;
	do {
		cout << "Please Enter Product cct:" << endl; //cct -> makat.
		cin >> product_cct;
		if (!validCct(product_cct)) {
			cout << "Invalid cct.Try again." << endl;
		}
	} while (!validCct(product_cct));
	// if the cct is valid.
	system("cls");
	ifstream Input;
	string Copy_String;
	ofstream Output;
	Output.open("Temp_Stock.txt");
	Input.open("Stock.txt");
	Product Temp_product;
	int Product_Amount;
	//load details of employee that connect to the system
	if (Input.is_open())
	{
		while (!(Input.eof()))
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				if (product_cct.compare(Copy_String) == 0)
				{
					Temp_product.cct = Copy_String;
					Input >> Temp_product.name;
					Input >> Temp_product.price;
					Input >> Copy_String;
					Product_Amount = ConvertToNum(Copy_String);
					if (Product_Amount > 0)
					{
						Product_Amount -= 1;
						toSend = 1;
					}
					else
					{
						cout << "product's amount too low, try  to add a different product" << endl;
						toSend = 0;
					}

				}
				else
				{
					Output << Copy_String << ' ';
					if (Copy_String[Copy_String.length() - 1] == '#')
					{
						Output << endl;
						continue;
					}
				}
			}
		}
		Output << Temp_product.cct << ' ' << Temp_product.name << ' ' << Temp_product.price << ' ' << Product_Amount << '#' << endl;
		Input.close();
		Output.close();
		Output.open("Stock.txt");
		Input.open("Temp_Stock.txt");
		while (!Input.eof())
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				Output << Copy_String << ' ';
				if (Copy_String[Copy_String.length() - 1] == '#')
				{
					Output << endl;
				}
			}
		}
	}
	Input.close();
	Output.close();
	if (toSend) {
		cout << "Product successfully added" << endl;
		updateBill(&bill, product_cct);
	}
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

int ConvertToNum(string Number)
{
	int Result = 0;
	int Index = 0;
	while (Number[Index] != '#')
	{
		Result *= 10;
		Result += (Number[Index] - '0');
		Index++;
	}
	return Result;
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
void deleteProductFromStock(string product_cct)
{
	ifstream Input;
	string Copy_String;
	ofstream Output;
	Output.open("Temp_Stock.txt");
	Input.open("Stock.txt");
	Product Temp_product;
	int Product_Amount;
	if (Input.is_open())
	{
		while (!(Input.eof()))
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				if (product_cct.compare(Copy_String) == 0)
				{
					Temp_product.cct = Copy_String;
					Input >> Temp_product.name;
					Input >> Temp_product.price;
					Input >> Copy_String;
					Product_Amount = ConvertToNum(Copy_String);
					Product_Amount += 1;
				}
				else
				{
					Output << Copy_String << ' ';
					if (Copy_String[Copy_String.length() - 1] == '#')
					{
						Output << endl;
						continue;
					}
				}
			}
		}
		Output << Temp_product.cct << ' ' << Temp_product.name << ' ' << Temp_product.price << ' ' << Product_Amount << '#' << endl;
		Input.close();
		Output.close();
		Output.open("Stock.txt");
		Input.open("Temp_Stock.txt");
		while (!Input.eof())
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				Output << Copy_String << ' ';
				if (Copy_String[Copy_String.length() - 1] == '#')
				{
					Output << endl;
				}
			}
		}
		Input.close();
		Output.close();
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
				break;
			}
		}
		if (index_to_delete == -1)
		{
			cout << "The product does not exist in the cart" << endl;
		}
		else if ((*(bill))->num_of_product > 1)
		{
			(*(bill))->sum -= (*bill)->product[index_to_delete]->price;
			Product** Assist = new Product* [(*(bill))->num_of_product - 1];
			int j = 0;
			for (int i = 0; i < (*(bill))->num_of_product; i++)
			{
				if (i == index_to_delete)
				{
					continue;
				}
				Assist[j] = new Product;
				Assist[j++] = (*bill)->product[i];
				deleteProductFromStock(product_cct);
			}
			delete((*bill)->product);
			(*bill)->product = Assist;
			(*(bill))->num_of_product--;
			Assist = nullptr;
			cout << "product has deleted" << endl;
		}
		else
		{
			(*(bill))->num_of_product = 0;
			delete((*bill)->product);
			(*bill)->product = nullptr;
			deleteProductFromStock(product_cct);
			cout << "product has deleted" << endl;
		}
	}
}

void makePayment(Bill * bill)
{
	system("cls");
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
		string CVV;
		bool friend_club = false;
		char user_freind_club_choice;
		bool flag = true;
		bool validFlag = true;
		fstream transaction;
		char ch;

		cout << "Is the client a club member? \n 1) Yes 2) No" << endl;
		cin >> user_freind_club_choice;
		do {
			if (user_freind_club_choice == '1')
				if (findFriendClub()) {
					friend_club = true;
					bill->sum *= 0.95;
				}
				else
				{
					cout << "friend member dose not found. do you want try again?\n 1) Yes 2) No" << endl;
					cin >> user_freind_club_choice;
				}
		} while (user_freind_club_choice == '1' && friend_club == false);

		cout << "The products are:" << endl;
		for (int i = 0; i < bill->num_of_product; i++)
		{
			cout << bill->product[i]->name << " - " << bill->product[i]->price << endl;
		}

		cout << "Amount to pay: " << bill->sum << endl;
		if (friend_club == true)
			cout << "You saved 5%! " << endl;
		do
		{
			cout << "How do you want to pay?: " << bill->sum << endl;
			cout << "1) Cash 2) Credit Card: " << endl;
			cin >> payment_type;
			switch (payment_type)
			{
			case '1':
			{
				cout << "How much money did you receive from the client?: " << endl;
				cin >> cash;
				if (cash >= bill->sum)
				{
					cout << "Money return: " << cash - bill->sum << endl;
					flag = false;
				}
				else
				{
					bill->sum -= cash;
					cout << "remind bill to pay is: " << bill->sum << endl;
				}

				
				break;
			}
			case '2':
			{
				do
				{
					cout << "How much money to charge: " << endl;
					do
					{
						cin >> cash;
						if (cash > bill->sum)
						{
							cout << "the amount to charge is bigger then bill amount try again." << endl;
						}
					} while (cash > bill->sum);
					if (!validFlag)
					{
						cout << "card number invalid" << endl;
					}

					cout << "card number" << endl;
					cin >> card_number;
					cout << card_number.length() << endl;
					if (card_number.length() != 8 && card_number.length() != 16)
					{
						validFlag = false;
					}
				} while ((card_number.length() != 8) && (card_number.length() != 16));
				validFlag = true;
				do
				{
					if (!validFlag)
					{
						cout << "validity invalid" << endl;
					}
					cout << "Enter validity: month/year" << endl;
					cin >> month >> ch >> year;
					if (year < lm.tm_year)
					{
						validFlag = false;
					}
					else
					{
						if ((year == lm.tm_year) && (month < lm.tm_mon))
						{
							validFlag = false;
						}
					}
				} while ((year == lm.tm_year) && (month < lm.tm_mon) || (year < lm.tm_year));
				validFlag = true;
				do
				{
					if (!validFlag)
					{
						cout << "CVV invalid " << endl;
					}
					cout << "Enter CVV: " << endl;
					cin >> CVV;
					if (CVV.length() != 3)
					{
						validFlag = false;
					}
					else
					{
						for (int i = 0; i < CVV.length(); i++)
						{
							if (!((CVV[i] >='0') && (CVV[i] <= '9')))
							{
								validFlag = false;
								break;
							}
							validFlag = true;
						}
						
					}

				} while (CVV.length() != 3 || !validFlag);
				if (cash == bill->sum)
				{
					flag = false;
				}
				else
				{
					bill->sum -= cash;
					cout << "remind bill to pay is: " << bill->sum << endl;
				}
				break;
			}
			default:
				cout << "Bad choice. Try again." << endl;
				break;
			}
		} while (flag);
		transaction.open("Transaction.txt", std::fstream::app);
		transaction <<'#' <<bill->current_account_number << ' ' << todaydate << ' ' << bill->id << ' ';
		for (int i = 0; i < bill->num_of_product; i++)
		{
			transaction << bill->product[i]->name << ' ' << bill->product[i]->cct << ' ' << bill->product[i]->price <<endl; //added cct to file
		}
		transaction << "Total bill: " << bill->sum << endl;
		transaction.close();
		cout << "transaction number: " << bill->current_account_number << " payed thank you" << endl;
		getchar();
		getchar();
		system("cls");
	}
}

bool findFriendClub() {
	string phone_number;
	bool phone_flag = true;
	do
	{
		if (!phone_flag)
		{
			cout << "phone number invalid" << endl;
		}
		cout << "Enter customer's phone number: " << endl;
		cin >> phone_number;
		if (phone_number.length() != 10)
		{
			phone_flag = false;
		}
	} while (phone_number.length() != 10);
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
