#pragma once
#include<fstream>
#include<string>
#include"Requirements_1_to_3.h"

void Orders_Report() //generate orders report of all time with the date that the order's done
{
	ifstream Input;
	string Transfer1;
	string Transfer2;
	string Transfer3;
	string Transfer4;
	Input.open("Orders.txt");
	cout << "----------------------------------------------" << endl;
	while (!Input.eof())
	{
		Input >> Transfer1;
		Input >> Transfer2;
		if (!Input.eof())
		{
			if (Transfer1[0] == '#')
			{
				cout << "Number of Transaction\t" << "Date "<< endl;
				cout << Transfer1 << "\t\t\t" << Transfer2 << endl << endl;
				Input >> Transfer1;
				Input >> Transfer2;
				Input >> Transfer3;
				Input >> Transfer4;
				cout << "product cct\t" << "  " << "product name\tproduct price\tproduct amount" << endl;
				while (Transfer1.compare("Total") != 0)
				{
					cout << Transfer1 << "\t\t  " << Transfer2 << "\t" << Transfer3 <<"\t\t"<< Transfer4 << endl;
					Input >> Transfer1;
					Input >> Transfer2;
					Input >> Transfer3;
					if (Transfer1.compare("Total") == 0)
					{
						break;
					}
					Input >> Transfer4;
				}
				cout << Transfer1 << ' ' << Transfer2 << ' ' << Transfer3 << ' ' << endl;
				cout << "----------------------------------------------" << endl;
				
			}
		}
	}
	Input.close();
}
