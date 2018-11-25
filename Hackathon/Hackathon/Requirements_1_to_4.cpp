#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;


typedef struct Product {
	string name;
	string cct = 0;
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
void creatBill();
void addProductToBill(Bill** bill);
bool validCct(string product_cct);
void updateBill(Bill*** bill);
void deleteExistProduct(Bill ** bill);


static int invoice_number = 0;

void newBill(Bill** bill) {
	*bill = new Bill; // ����� ��� ������ ����� ������ ����� ����� �����
	invoice_number++;
}

void newProduct(Product** product) {
	*product = new Product; // ����� ��� ������ ����� ������ ����� ����� �����
}

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill()
{
	Bill *bill;
	newBill(&bill);
	bill->current_account_number = invoice_number;
	bool flag = true;
	char user_choise;

	// �� ����� ����� ������ ��� ������� ����� ����� ����� ����� �� ����
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
		case '3': // ����� ��� ������ ������ �� �� ����� ����� ������ ������
			break;
		case '4': // �� ����� ����� ����� ������ ���� ��� ����� -- ����� ����� ��������
				  // ����� ��� ������ ������ �� �� ����� ����� ������ ������
			break;
		default:
			break;
		}
	} while (flag);
}

void addProductToBill(Bill** bill)
{
	string product_cct = 0;
	do {
		cout << "Please Enter Product cct:" << endl; //cct -> makat.
		cin >> product_cct;
		if (!validCct(product_cct)) {
			cout << "Invalid cct.Try again." << endl;
		}
	} while (!validCct(product_cct));
	// if the cct is valid.
	cout << "Product successfully added" << endl;
	updateBill(&bill);

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

void updateBill(Bill*** bill) {
	// ����� ���� ������ �� ����� �� ���� ���� ����� ������ price
	double price = 0;
	string name;
	int cct = 0;
	// ����� ������� ������
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
	
	// ���� �������� ���� ������ ���� ����� ���� ����� ����� ���� ����� ����� ���� ���� ����� �� ����� ���� ������

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
		string product_cct = 0;
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
		}
	}

	//�� ����� ������ �� ����� ���� �����

}
