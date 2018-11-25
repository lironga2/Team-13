#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

typedef struct
{
	int day;
	int month;
	int year;
}Date;

void Add_Club_Member()
{
	string first_name;
	string last_name;
	string id;
	string phone_number;
	Date bDay;
	string city;
	fstream clubMembers;
	char ch;
	cout << "Enter customer first name" << endl;
	std::getline(std::cin, first_name);
	cin.ignore();
	cout << "Enter customer last name" << endl;
	std::getline(std::cin, last_name);
	cin.ignore();
	cout << "Enter customer id" << endl;
	std::getline(std::cin, id);
	cin.ignore();
	cout << "Enter customer phone number" << endl;
	std::getline(std::cin, phone_number);
	cin.ignore();
	cout << "Enter customer bDay : dd.mm.yyyy" << endl;
	cin >> bDay.day >> ch >> bDay.month >> ch >> bDay.year;
	cout << "Enter customer city" << endl;
	std::getline(std::cin, city);
	cin.ignore();
	clubMembers.open("clubMembers.txt", std::fstream::app);
	clubMembers << id << ' ' << first_name << ' ' << last_name << ' ' << bDay.day << '.' << bDay.month << '.' << bDay.year << ' ' << city << ' ' << phone_number << endl;
	clubMembers.close();
}
