//
//	BankAccount.h
//

#ifndef BankAccount_h
#define BankAccount_h
#include "Account.h"

class BankAccount : public Account
{
public:
	BankAccount();
	double get_balance();
	void set_balance();
	void deposit(double);
	bool withdraw(double);
	// record deposit and withdraw transaction
	void record_transaction(char, double);
	// record cash balance
	void record_balance();
	// print doposit and withdraw transaction
	void print_history();
private:
	double balance;
};

#endif