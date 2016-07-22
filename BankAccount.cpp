//
//	BankAccount.cpp
//

#define _CRT_SECURE_NO_WARNINGS
#include "BankAccount.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <string>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::setw;
using std::string;
using std::ios;

BankAccount::BankAccount()
:Account()
{
	set_balance();
}


double BankAccount::get_balance()
{
	return balance;
}

// read cash balance from cash_history.txt
// if can not open file, set cash balance 10000
void BankAccount::set_balance()
{
	ifstream file1("cash_history.txt");
	if (file1.is_open() == false)
	{
		balance = 10000;
	}
	else
	{
		file1 >> balance;
	}
}

void BankAccount::deposit(double value)
{
	balance = balance + value;
}

bool BankAccount::withdraw(double value)
{
	if (value > balance)
		return false;
	else
	{
		balance = balance - value;
	}
	return true;
}

// record manipulate, amount and time of transaction
void BankAccount::record_transaction(char choice, double amount)
{
	time_t moment;
	moment = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&moment);

	ofstream file2;
	file2.open("bank_transaction_history.txt", ios::app);
	file2 << ((choice == '2') ? "Deposit" : "Withdraw")
		<< "   $" << amount << "   " << asctime(timeinfo);
	file2.close();
}

// record cash balance to cash_history.txt
void BankAccount::record_balance()
{
	double value = balance;
	ofstream history;
	history.open("cash_history.txt");
	history << value;
	history.close();
}

// print transaction history from bank_transaction_history.txt
void BankAccount::print_history()
{
	string manipulate;
	string amount;
	string date1;
	string date2;
	string date3;
	string date4;
	string date5;

	ifstream file3("bank_transaction_history.txt", ios::in);
	while (file3 >> manipulate >> amount >> date1
		>> date2 >> date3 >> date4 >> date5)
	{
		cout << setw(8) << manipulate << setw(8) << amount << setw(5)
			<< date1 << setw(5) << date2 << setw(4)
			<< date3 << setw(10) << date4 << setw(6) << date5;
		cout << endl;
	}
}