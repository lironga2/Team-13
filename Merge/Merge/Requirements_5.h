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
void UpdateDate() //update for today date
{
	if (currDate_Flag)
	{
		tm.tm_mon += 1;
		tm.tm_year += 1900;
		currDate_Flag = false;
	}
	sprintf(currDate, "%d.%d.%d", tm.tm_mday, tm.tm_mon, tm.tm_year);
}



bool checkIfNum(string temp) { //func that check if all chars in string are nums
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] > '9' || temp[i] < '0')
			return false;
	}
	return true;
}

bool checkIfNum(char temp) { //func that check if char is num
	return temp >= '0' && temp <= '9';
}

double convertStringToNum(string temp) //convert regular string to num
{
	int multy = 1;
	double num_to_return = 0;
	if(!checkIfNum(temp))
	{ 
		return -999;
	}
	if (checkIfNum(temp))
	{
		for (int i = temp.length()-1; i >= 0; i--)
		{
			num_to_return += multy * (temp[i] - '0');
			multy *= 10;
		}
	}
	return num_to_return;
}

void Add_Club_Member(string worker_id) //add new club member to clubmembers.txt with the id of worker and the date
{
	UpdateDate();
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
		if (id.length() != 9 || !checkIfNum(id))
		{
			flag = false;
		}
		else
			flag = true;
	} while (!flag);
	cout << "Enter customer first name" << endl;
	std::getline(std::cin, first_name);
	cout << "Enter customer last name" << endl;
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
	clubMembers.open("ClubMember.txt", std::fstream::app); //write to end of file
	clubMembers << id << ' ' << first_name << ' ' << last_name << ' ' << bDay.day << '.' << bDay.month << '.' << bDay.year << ' ' << city << ' ' << phone_number << ' ' << currDate << ' ' << worker_id << endl;
	clubMembers.close();
	system("cls");
	cout << "Club member added" << endl;
}

