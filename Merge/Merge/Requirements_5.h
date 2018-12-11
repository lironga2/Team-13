#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <time.h>
using namespace std;

static char currDate[30];
time_t t = time(NULL);
struct tm tm = *localtime(&t);
static bool currDate_Flag = true;

typedef struct
{
	int day;
	int month;
	int year;
}Date;

void Add_Club_Member(string worker_id)
{
	if (currDate_Flag)
	{
		tm.tm_mon += 1;
		tm.tm_year += 1900;
		currDate_Flag = false;
	}
	sprintf(currDate, "%d.%d.%d", tm.tm_mday, tm.tm_mon, tm.tm_year);
	cout << currDate;
	string first_name;
	string last_name;
	string id;
	string phone_number;
	Date bDay;
	string city;
	fstream clubMembers;
	char ch;
	cin.ignore();
	bool flag = true;
	do
	{
		if (!flag)
		{
			cout << "Id invalid" << endl;
		}
		cout << "Enter customer id" << endl;
		std::getline(std::cin, id);
		if (id.length() != 9)
		{
			flag = false;
		}
	} while (id.length() != 9);
	cout << "Enter customer first name" << endl;
	//cin.ignore();
	std::getline(std::cin, first_name);
	cout << "Enter customer last name" << endl;
	//cin.ignore();
	std::getline(std::cin, last_name);
	cout << "Enter customer bDay : day.month.year" << endl;
	cin >> bDay.day >> ch >> bDay.month >> ch >> bDay.year;
	cout << "Enter customer city" << endl;
	cin.ignore();
	std::getline(std::cin, city);
	flag = true;
	do
	{
		if (!flag)
		{
			cout << "phone number invalid" << endl;
		}
		cout << "Enter customer phone number" << endl;
		std::getline(std::cin, phone_number);
		if (phone_number.length() != 10)
		{
			flag = false;
		}
	} while (phone_number.length() != 10);
	//cin.ignore();
	clubMembers.open("ClubMember.txt", std::fstream::app);
	clubMembers << id << ' ' << first_name << ' ' << last_name << ' ' << bDay.day << '.' << bDay.month << '.' << bDay.year << ' ' << city << ' ' << phone_number << ' ' << currDate << ' ' << worker_id << endl;
	clubMembers.close();
}

