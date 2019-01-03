#pragma once
#include <iostream>
#include<string>
#include<fstream>

using namespace std;

static bool Curr_Sale = true;

void Create_Update_Sale();
void Remove_Sale(bool* IfSale);

void Update_Sale_Flag(bool* IfSale)  // change the flag of store sale, if true sale on.
{
	ifstream Input;
	ofstream Output;
	string Search;
	Input.open("Financial balance.txt");
	while (!Input.eof())
	{
		Input >> Search;
		if (Search.compare("Yes") == 0)
		{
			(*IfSale) = true;
			break;
		}
		if (Search.compare("No") == 0)
		{
			(*IfSale) = false;
			break;
		}
	}
	Input.close();
}

void Update_Sale(double* Sale_Percent,double* sale) //updaate the current sale in store and store it in txt of financial balance
{
	if (Curr_Sale)
	{
		ifstream Input;
		ofstream Output;
		string Search;
		Input.open("Financial balance.txt");
		while (!Input.eof())
		{
			Input >> Search;
			if (Search.compare("Yes") == 0)
			{
				Input >> (*Sale_Percent);
				(*sale) -= ((*Sale_Percent) / 100);
				break;
			}
		}
		Input.close();
		Curr_Sale = false;
	}
}

void Sale_Management(bool* IfSale, double* Sale_Percent,double* sale) //sale menu
{
	char Option;
	do {
		cout << "1) to Create Sale or update sale percent" << endl;
		cout << "2) to remove current sale" << endl;
		cout << "0) to get back" << endl;
		cin >> Option;
		if (Option != '0' && Option != '1' && Option != '2')
		{
			cout << " Invalid Option" << endl;
		}
	} while (Option != '0' && Option != '1' && Option != '2');
	switch (Option)
	{
		case '1':
		{
			Update_Sale_Flag(IfSale);
			if (*IfSale)
			{
				Update_Sale(Sale_Percent,sale);
				cout << "The current sale is: " << (*Sale_Percent) << '%' << endl;
			}
			else
			{
				cout << "There is no sale" << endl;
			}
			Create_Update_Sale();
			break;
		}
		case'2':
		{
			Remove_Sale(IfSale);
		}
		default:
			break;
	}
}

void Create_Update_Sale() // create new sell of store and output it to financial balance txt with the % and the word YES
{
	ifstream Input;
	ofstream Output;
	string Transfer;
	int The_Sale;
	bool flag = false;
	do
	{
		if (flag)
		{
			cout << "Discount isn't valid" << endl;
		}
		cout << "Enter discount between 1% -> 50%: ";
		cin >> The_Sale;
		if (!(The_Sale >= 1 && The_Sale <= 50))
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	} while (flag);
	Input.open("Financial balance.txt");
	Output.open("Temp.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
		if (!Input.eof())
		{
			if (Transfer.compare("revenue:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("box:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("expenses:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("money:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("sale:") == 0)
			{
				Output << Transfer << endl;
				Output << "Yes" << ' ' << The_Sale;
				break;
			}
			Output << Transfer << ' ';
		}
	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Financial balance.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
			if (Transfer.compare("revenue:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("box:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("expenses:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("money:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("sale:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			Output << Transfer << ' ';
		
	}
	Input.close();
	Output.close();
	system("cls");
	cout << "Sale of: " << The_Sale << "% successfully updated" << endl;
} 

void Remove_Sale(bool* IfSale) //remove the sell by change the financial balance.txt - change yes to no and change the sell % to 0.
{
	ifstream Input;
	ofstream Output;
	string Transfer;

	Input.open("Financial balance.txt");
	Output.open("Temp.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
		if (!Input.eof())
		{
			if (Transfer.compare("revenue:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("box:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("expenses:") == 0)
			{
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("money:") == 0)
			{
				Output << Transfer << ' ';
				Input >> Transfer;
				Output << Transfer << endl;
				continue;
			}
			if (Transfer.compare("sale:") == 0)
			{
				Output << Transfer << endl;
				Output << "No" << ' ' << 0;
				break;
			}
			Output << Transfer << ' ';
		}
	}
	Input.close();
	Output.close();
	Input.open("Temp.txt");
	Output.open("Financial balance.txt");
	while (!Input.eof())
	{
		Input >> Transfer;
		if (Transfer.compare("revenue:") == 0)
		{
			Output << Transfer << endl;
			continue;
		}
		if (Transfer.compare("box:") == 0)
		{
			Output << Transfer << ' ';
			Input >> Transfer;
			Output << Transfer << endl;
			continue;
		}
		if (Transfer.compare("expenses:") == 0)
		{
			Output << Transfer << endl;
			continue;
		}
		if (Transfer.compare("money:") == 0)
		{
			Output << Transfer << ' ';
			Input >> Transfer;
			Output << Transfer << endl;
			continue;
		}
		if (Transfer.compare("sale:") == 0)
		{
			Output << Transfer << endl;
			continue;
		}
		Output << Transfer << ' ';

	}
	Input.close();
	Output.close();
}