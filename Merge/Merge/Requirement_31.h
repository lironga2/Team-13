#pragma once
#include<iostream>
#include<fstream>
#include<string>

#define SIZE 6

using namespace std;

typedef struct The_Product 
{
	string name;
	string cct;
	double price = 0;
	int amount = 0;
};

typedef struct Order 
{
	The_Product* Product;
};

static Order* Supllayer;


void Install_Supllayer_Product()
{
	Supllayer = new Order[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
	Supllayer[i].Product = new The_Product;
	}
	Supllayer[0].Product->cct = "101";
	Supllayer[0].Product->name = "MacBook";
	Supllayer[0].Product->price = 6000;
	Supllayer[1].Product->cct = "102";
	Supllayer[1].Product->name = "DellPc";
	Supllayer[1].Product->price = 2250;
	Supllayer[2].Product->cct = "103";
	Supllayer[2].Product->name = "OpticMouse";
	Supllayer[2].Product->price = 60;
	Supllayer[3].Product->cct = "104";
	Supllayer[3].Product->name = "IpadPro";
	Supllayer[3].Product->price = 2000;
	Supllayer[4].Product->cct = "105";
	Supllayer[4].Product->name = "IphoneXs";
	Supllayer[4].Product->price = 3000;
	Supllayer[5].Product->cct = "106";
	Supllayer[5].Product->name = "AirPods";
	Supllayer[5].Product->price = 350;
}

void Print_Supllayer_Product()
{
	cout << "Supllayer product table:" << endl;
	cout << "product cct\t" << "  " << "product name\tproduct price" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << Supllayer[i].Product->cct << "\t\t  " << Supllayer[i].Product->name << "\t" << Supllayer[i].Product->price << endl;
		cout << "----------------------------------------------" << endl;
	}
}