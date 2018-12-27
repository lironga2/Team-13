//#pragma once
//#include<string>
//#include<iostream>
//#include"Requirement_31.h"
//
//using namespace std;
//
////void Add_Product_To_Order();
//
//void Add_Product_To_Order()
//{
//	//Install_Supplier_Product();
//	string Cct;
//	char Option;
//	bool Flag = false;
//	bool Try_Againe = true;
//	while (Try_Againe)
//	{
//		cout << "Enter product to: ";
//		cin >> Cct;
//		for (int i = 0; i < Supplier_Product_Amount; i++)
//		{
//			if (Supplier[i].Product->cct.compare(Cct) == 0)
//			{
//				Supplier[i].Product->amount++;
//				Flag = true;
//				Try_Againe = false;
//			}
//		}
//		if (Flag)
//		{
//			cout << "Product successfully added" << endl;
//		}
//		else
//		{
//			cout << "Product cct Invalid " << endl;
//			cout << "if you want try again press Y|y else press any key to continue" << endl;
//			cin >> Option;
//			if (Option != 'Y' && Option != 'y')
//			{
//				Try_Againe = false;
//			}
//		}
//	}
//
//}
