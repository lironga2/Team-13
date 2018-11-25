#include "Requirements_1_to_4.h"

typedef struct{
	double sum = 0;
	int num_of_product = 0;
	bool club_member = false;
	int current_account_number;
}Bill;


void newBill(Bill** bill) {
	Bill *bill = new Bill; // בדיקה האם היצירה נכשלה ושליחת הודעת שגיאה בהתאם
	invoice_number++;
}

//The menu that appears after selecting Create new account from the main menu. Demand Analysis Number 1.
void creatBill()
{
	bool flag = true;
	Bill *bill;
	newBill(&bill);
	bill->current_account_number = invoice_number;

	char user_choise;
	cout << "1) Add a new product:" << endl;
	cout << "2) Delete an existing product:" << endl;
	cout << "3) Making a payment:" << endl;
	cout << "4) Back:" << endl;
	// לא לשכוח לבדוק תקינות קלט ולהוסיף הודעת שגיאה במקרה והקלט לא תקין
	do {
		switch (user_choise)
		{
		case '1':
			addProductToBill(&bill);
			break;
		case '2':
			deleteExistProduct(&bill);
			break;
		case '3': // לשנות דגל לשלילי ולמחוק כל מה שקיים בקובץ החשבון הנוכחי
			break;
		case '4': // לא לשכוח שחרור הקצאה לחשבון החדש וגם לעשות -- למספר חשבון הגלובאלי
				  // לשנות דגל לשלילי ולמחוק כל מה שקיים בקובץ החשבון הנוכחי
			break;
		default:
			break;
		}
	} while (flag);
}

void addProductToBill(Bill** bill)
{
	int product_cct = 0;
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
bool validCct(int product_cct) {
	// ריצה על מאגר המקטים ובדיקה אם המקט קיים
	return true;
	return false;
}

void updateBill(Bill*** bill) {
	// משיכת מחיר מהקובץ של המוצר של מספר המקט שהוזן למשתנה price
	double price = 0;
	(*(*bill))->sum += price;
	(*(*bill))->num_of_product++;
	// ברגע שמוסיפים מוצר לחשבון צריך לכתוב אותו לקובץ בשביל שכדי שנרצה למחוק מוצר נוכל לבדוק אם המוצר קיים בחשבון
}

void deleteExistProduct(Bill ** bill)
{
	int product_cct = 0;
	cout << "Enter cct to delete product" << endl;
	// קריאה מקובץ שאליו הפריטים שהתווספו לחשבון נכתבו בפונקציה לעל (אפדייט ביל) כדי לבדוק שהמוצר קיים בחשבון
	
}
