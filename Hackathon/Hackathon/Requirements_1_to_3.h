#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static int invoice_number = 0;

typedef struct Product {
	string name;
	string cct;
	double price = 0;
};

typedef struct Bill {
	double sum = 0;
	int num_of_product = 0;
	bool club_member = false;
	int current_account_number;
	Product** product;
};



void newBill(Bill** bill);

void newProduct(Product** product);

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill(int id);

void addProductToBill(Bill** bill);
// A function that checks if the cct that entered in a function addProductToBill() exists in the database.
bool validCct(string product_cct);

void updateBill(Bill*** bill,string product_cct);

void deleteExistProduct(Bill **bill);