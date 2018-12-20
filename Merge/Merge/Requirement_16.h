#pragma once

void editTxtGiftCard(int giftcard_amount, string giftcard_number)
{
	ifstream Input;
	string Copy_String;
	ofstream Output;
	string temp_giftcard_number;
	string date;
	int amount;

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
					Input >> amount;
					Input >> date;
					

				}
				else
				{
					Output << Copy_String << ' ';
					Input >> Copy_String;
					Output << Copy_String << ' ';
					Input >> Copy_String;
					Output << Copy_String << endl;
				}
			}
		}
		Output << temp_giftcard_number << ' ' << giftcard_amount << ' '<< date << endl;
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
				Input >> Copy_String;
				Output << Copy_String << ' ';
				Input >> Copy_String;
				Output << Copy_String << endl;
			}
		}
		Input.close();
		Output.close();
	}
}

int checkIfGiftCardExist()
{
	fstream file_giftcard;
	string number_giftcard_to_cmp;
	string number_giftcard;
	string date;
	int gift_use = 0;
	int giftcard_amount;

	cout << "enter number of giftcard with the format #Num" << endl;
	cin >> number_giftcard;
	file_giftcard.open("GiftCard.txt");
	if (file_giftcard.is_open())
	{
		while (!file_giftcard.eof())
		{
			file_giftcard >> number_giftcard_to_cmp;
			if ((number_giftcard.compare(number_giftcard_to_cmp) == 0))
			{
				file_giftcard >> giftcard_amount;
				file_giftcard >> date;
				if (giftcard_amount < 1)
				{
					cout << "your giftcard is empty, you cant use it." << endl;
					return 0;
				}
				else
				{
					cout << "what is the value that u want to use from your giftcard? Max:" << giftcard_amount << endl;
					do {
						if (gift_use)
							cout << "you choosed higher use then the maximum value of your giftcard, try again" << endl;
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
