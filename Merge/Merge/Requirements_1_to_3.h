#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Requirement_26.h"
#include <time.h>
#include<stdlib.h>
using namespace std;

static int invoice_number = 0;  //static var change to the last transaction every new sell
static double sale = 1; // global sale
static double Sale_Percent = 0;
static bool ifSale = false; //var of store sale that manager can change
static bool if_club_member; //var to add 5% discount if client club member
static bool extra_discount; //var of discount that level 2 or 3 can give

typedef struct Product {
	string name;
	string cct;
	double price = 0;
};

typedef struct Bill { //dynamic struct of bill
	long double sum = 0;
	int num_of_product = 0;
	bool club_member = false;
	int current_account_number;
	Product** product;
	bool friend_club = false;
	string id;
	int level;
};

#pragma once
#include"Requirement_17.h"
#include "Requirement_16.h"


static char todaydate[30];
time_t l = time(NULL);
struct tm lm = *localtime(&l);
static bool Date_Flag = true;

void newBill(Bill** bill);
void newProduct(Product** product);
void creatBill(string id, int level);
void addProductToBill(Bill** bill);
bool validCct(string product_cct);
void updateBill(Bill*** bill, string product_cct);
void deleteExistProduct(Bill ** bill);
void makePayment(Bill *bill);
bool findFriendClub(string test="1234");
int ConvertToNum(string Number);
void backProductToStock(string product_cct);
void Manager_Or_Shift_Manager_Options(Bill* bill);



void newBill(Bill** bill) { //create new bill
	bool friend_club = false;
	string user_freind_club_choice;
	int Freind_Club_Choice;
	*bill = new Bill;
	if (!bill) {
		cout << "Bad allocate." << endl;
		exit(1);
	}
	invoice_number++;
	do
	{
		
		cout << "Is the client a club member? \n 1) Yes 2) No" << endl;
		cin >> user_freind_club_choice;
		Freind_Club_Choice = convertStringToNum(user_freind_club_choice);
		if (Freind_Club_Choice != 1 && Freind_Club_Choice != 2)
		{
			cout << "Option invalid try again" << endl;
		}
	} while (Freind_Club_Choice != 1 && Freind_Club_Choice != 2);
	do {
		if (Freind_Club_Choice == 1)
			if (findFriendClub()) {
				friend_club = true;
				if_club_member = friend_club;
			}
			else
			{
				cout << "friend member dose not found. do you want try again?\n 1) Yes 2) No" << endl;
				cin >> user_freind_club_choice;
			}
	} while (Freind_Club_Choice == 1 && friend_club == false);
}

void newProduct(Product** product) { //allocate new product 
	*product = new Product;
	if (!product) {
		cout << "Bad allocate." << endl;
		exit(1);
	}
}

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill(string id, int level)
{
	if (Date_Flag)
	{
		lm.tm_mon += 1;
		lm.tm_year += 1900;
		Date_Flag = false;
	}
	Update_Sale_Flag(&ifSale);
	if (ifSale)
	{
		Update_Sale(&Sale_Percent, &sale);
	}
	sprintf(todaydate, "%d.%d.%d", lm.tm_mday, lm.tm_mon, lm.tm_year);
	cout << todaydate << endl;
	Bill *bill;
	newBill(&bill);
	int Transaction_Number = 0;
	int manager_password;
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
	bill->level = level;
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
		cout << "4) Shift manager / Manager options:" << endl; //will work only with general pass for this options
		cout << "5) Back:" << endl;
		cin >> user_choise;
		switch (user_choise)
		{
		case '1':
			addProductToBill(&bill);
			break;
		case '2':
			deleteExistProduct(&bill);
			break;
		case '3': 
			makePayment(bill); //finish bill and get payment
			flag = false;
			break;
		case '4':
			if (bill->level >= 2)
			{
				Manager_Or_Shift_Manager_Options(bill);
			}
			else
			{
				cout << "please enter Manager password " << endl;
				cin >> manager_password;
				if (manager_password == 1234)
				{
					Manager_Or_Shift_Manager_Options(bill);
				}
			}
			break;
		case '5': 
			flag = false;
			if (bill->num_of_product)
			{
				for (int i = 0; i < bill->num_of_product; i++)
				{
					backProductToStock(bill->product[i]->cct);
				}
			}
			break;
		default:
			cout << "Invalid choice. Try again." << endl;
			break;
		}
	} while (flag);
}

void addProductToBill(Bill** bill) //add the product that allocate to the current bill
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
	Output.open("Temp.txt");
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
					if (Product_Amount > 0) //wont add product from stock if amount 0
					{
						Product_Amount -= 1;
						toSend = 1;
					}
					else
					{
						cout << "product's amount too low, try to add a different product" << endl;
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
		Input.open("Temp.txt");
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
			Stock.close();
			return true;
		}
	}
	Stock.close();
	return false;
}

int ConvertToNum(string Number) //convert number of transaction to int (number of transaction in format Number#)
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

void updateBill(Bill*** bill, string product_cct) { //get the price from stock file to calculate the total price
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
			if (if_club_member) //give 5% discount if club member
			{
				price = price*0.95;
				if (ifSale)
				{
					price *= sale;
				}
			}
			else if (ifSale)
			{
				price *= sale;
			}
			Stock.close();
			break;
		}
	}
	(*(*bill))->sum += price;
	int old_size = (*(*bill))->num_of_product; //allocate more memory to bill after adding product
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
		Product** Assist = new Product *[temp]; //copy old struct with the added product to new struct
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
void backProductToStock(string product_cct) //bring the product back to stock if deleted from bill
{
	ifstream Input;
	string Copy_String;
	ofstream Output;
	Output.open("Temp.txt");
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
					Product_Amount += 1; //add amount of product back
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
		Input.open("Temp.txt");
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
void deleteExistProduct(Bill ** bill) //delete product from bill
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

		for (int i = 0; i<(*(bill))->num_of_product; i++)
		{
			if (product_cct.compare((*(bill))->product[i]->cct) == 0) {
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
			Product** Assist = new Product*[(*(bill))->num_of_product - 1];
			int j = 0;
			for (int i = 0; i < (*(bill))->num_of_product; i++)
			{
				if (i == index_to_delete)
				{
					continue;
				}
				Assist[j] = new Product;
				Assist[j++] = (*bill)->product[i];
				backProductToStock(product_cct);
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
			backProductToStock(product_cct);
			cout << "product has deleted" << endl;
		}
	}
}

void makePayment(Bill * bill) //finish bill and get pay
{
	system("cls");
	if (bill->num_of_product == 0)
	{
		cout << "There is no products in the bill" << endl;
	}
	else
	{
		char payment_type;
		float club_member_discount = 0.95;
		long double cash = 0;
		string card_number;
		int month;
		int year;
		string CVV;
		char user_giftcard_choice;
		bool flag = true;
		bool validFlag = true;
		fstream transaction;
		char ch;
		int cash_from_giftcard = 0;
		string manager_password;
		cout << "is the client have valid giftcard? 1) Yes 2) No" << endl;
		cin >> user_giftcard_choice;
		if ((user_giftcard_choice == '1'))
		{
			cout << "please enter Manager password " << endl;
			cin >> manager_password;
			if ((manager_password.compare("1234") == 0))
			{
				if (user_giftcard_choice == '1')
					cash_from_giftcard = checkIfGiftCardExist();
			}
		}

		if (if_club_member)
		{
			cout << "You saved 5% because you are our club member!" << endl;
		}
		for (int i = 0; i < bill->num_of_product; i++)
		{
			cout << bill->product[i]->name << " - " << bill->product[i]->price << endl;
		}

		if (cash_from_giftcard)
		{
			bill->sum -= cash_from_giftcard;
			cout << "after the use of the giftcard amount, your final bill is:" << bill->sum << endl;
		}
		else
			cout << "Amount to pay: " << bill->sum << endl;
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
							if (!((CVV[i] >= '0') && (CVV[i] <= '9')))
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
		transaction << '#' << bill->current_account_number << ' ' << todaydate << ' ' << bill->id << endl;
		for (int i = 0; i < bill->num_of_product; i++)
		{
			transaction << bill->product[i]->cct << ' ' << bill->product[i]->name << ' ' << bill->product[i]->price << endl;
		}
		transaction << "Total bill: " << bill->sum << endl;
		transaction.close();
		cout << "transaction number: " << bill->current_account_number << " payed thank you" << endl;
		getchar();
		getchar();
		system("cls");
		if_club_member = false;
		//extra_discount = false;
	}
}

bool findFriendClub(string test) //check if client club member
{
	string phone_number;
	bool phone_flag = true;
	if (test.compare("1234") == 0)
	{
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
	}
	else
	{
		phone_number = test;
	}
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

void Manager_Or_Shift_Manager_Options(Bill* bill) //if general worker connected and want to use other level options
{
	bool flag = true;
	string user_choise;
	do
	{
		cout << "1) Give the client a discount" << endl;
		cout << "0) Back" << endl;
		cin >> user_choise;
		int Option;
		Option = convertStringToNum(user_choise);
		switch (Option)
		{
		case 1:
			giveCleintDiscount(&bill);
			break;
		case 0:
			flag = false;
			break;
		default:
			cout << "option invalid try again" << endl;
			break;
		}
	} while (flag);
}