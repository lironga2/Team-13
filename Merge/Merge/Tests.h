#pragma once
#include"minunit.h"
#include"Requirement_21.h"
#include"Requirements_5.h"
#include<time.h>
#include <stdlib.h>
int tests_run = 0;

static char * test_if_worker_found()
{
	mu_assert("Error in check if worker found, should be true", checkIfWorkerFound("202020202") == true);
	return 0;
}
static char * test_return_role()
{
	mu_assert("Error in check return role, 2 should be shift-manager", returnRole(2) == "Shift-manager");
	return 0;
}

static char * test_check_If_Valid_Id()
{
	mu_assert("Error in check if valid id, should id sent should be false", checkIfValidId("2") == false);
	return 0;
}

static char * test_check_If_Num()
{
	mu_assert("Error in check if num, should be true sent should be true", checkIfNum("2") == true);
	return 0;
}
static char * test_convert_String_To_Num()
{
	mu_assert("Error in convert string to num, should be int - 1234 should be true", convertStringToNum("1234") == 1234);
	return 0;
}
static char * test_valid_Cct()
{
	mu_assert("Error in valid cct, should be true ", validCct("101") == true);
	return 0;
}
static char * test_find_friend_club()
{
	mu_assert("Error in finding friend club, should be true ", findFriendClub("0526256397") == true);
	return 0;
}
static char * test_login()
{
	mu_assert("Error in login to store system,should be: your log to system", Login("l", "1") == "your log to system");
	return 0;
}
static char * test_product_In_Stock()
{
	mu_assert("Error test product in store,should be: 1", productInStock("101") == 1);
	return 0;
}
static char * test_check_If_Gift_Card_Exist()
{
	mu_assert("Error test gift card exist #1,should be: 1", checkIfGiftCardExist("#1") == 1);
	return 0;
}
static char * test_convert_to_string()
{
	mu_assert("Error test convert to string 12345,should be: 12345#", Convert_To_String(12345) == "12345#");
	return 0;
}
static char * test_check_If_All_String_Num()
{
	mu_assert("Error in check if num, should be true sent should be true", checkIfNum("1234") == true);
	return 0;
}
static char * test_if_Load_Details()
{
	mu_assert("Error in check if load details, should be gilad", load_details("giladco", "YES") == "gilad");
	return 0;
}
static char * test_is_valid()
{
	mu_assert("Error in check if is valid, should be true", isValid("lironga2", "123456") == true);
	return 0;
}


static char * all_tests()
{
	mu_run_test(test_if_worker_found);
	mu_run_test(test_return_role);
	mu_run_test(test_check_If_Valid_Id);
	mu_run_test(test_check_If_Num);
	mu_run_test(test_convert_String_To_Num);
	mu_run_test(test_valid_Cct);
	mu_run_test(test_find_friend_club);
	mu_run_test(test_login);
	mu_run_test(test_product_In_Stock);
	mu_run_test(test_check_If_Gift_Card_Exist);
	mu_run_test(test_convert_to_string);
	mu_run_test(test_check_If_All_String_Num);
	mu_run_test(test_if_Load_Details);
	mu_run_test(test_is_valid);
	return 0;
}


int test()
{

	char *result = all_tests();

	if (result != 0) {
		cout << result << endl;
	}
	else {
		cout << "ALL TESTS PASSED" << endl;
	}
	cout << "Tests run: " << tests_run << endl;

	return result != 0;
}
