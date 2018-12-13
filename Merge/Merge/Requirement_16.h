#pragma once
#include "Requirement_6_to_12_and_15.h"
int checkIfGiftCardExist()
{
	fstream file_giftcard;
	string number_giftcard_to_cmp;
	string number_giftcard;
	int gift_use=0;
	int giftcard_amount;

	cout << "enter number of giftcard with the format #Num" << endl;
	cin >> number_giftcard;
	file_giftcard.open("GiftCard.txt");
	if (file_giftcard.open)
	{
		while (!file_giftcard.eof)
		{
			file_giftcard >> number_giftcard_to_cmp;
			if ((number_giftcard.compare(number_giftcard_to_cmp) == 0))
			{
				file_giftcard >> giftcard_amount;
				if (giftcard_amount < 1)
				{
					cout << "your giftcard is empty, you cant use it." << endl;
					break;
				}
				else
				{
					cout << "what is the value that u want to use from your giftcard? Max:" << giftcard_amount << endl;
					do {
						if (gift_use)
							cout << "you choosed higher use then the maximum value of your giftcard" << endl;
						cin >> gift_use;
					} while (gift_use > giftcard_amount);
					giftcard_amount -= gift_use;
				}
				editTxtGiftCard(giftcard_amount, number_giftcard); //send giftcard num and new amount to update in txt
				return gift_use; // return to decrease this amount in bill
			}
		}
		cout << "giftcard not exist in system" << endl;
	}
	file_giftcard.close();
}
void editTxtGiftCard(int giftcard_amount,string giftcard_number)
{
	ifstream Input;
	string Copy_String;
	ofstream Output;
	string temp_giftcard_number;

	Output.open("Temp.txt");
	Input.open("GiftCard.txt");
	if (Input.is_open())
	{
		while (!(Input.eof()))
		{
			Input >> Copy_String;
			if (!Input.eof())
			{
				if (giftcard_number.compare(Copy_String) == 0)
				{
					temp_giftcard_number = Copy_String;
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
		Output <<"#" << temp_giftcard_number <<' ' << giftcard_amount << endl;
		Input.close();
		Output.close();
		Output.open("GiftCard.txt");
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