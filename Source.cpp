//
//	Financial Account Management System Project
//

#include <iostream>
#include <string>
#include "Account.h"
#include "BankAccount.h"
#include "StockAccount.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	char choice1 = '0', choice2 = '0', choice3 = '0';
	double deposit_value = 0;
	double withdraw_value = 0;
	BankAccount bank_account;
	StockAccount stock_account;

	do{
		cout << "\nWelcome to the Account Management System."
			<< "\nPlease select an account to access:"
			<< "\n1. Stock Portfolio Account"
			<< "\n2. Bank Account"
			<< "\n3. Exit"
			<< "\nOption: ";
		// asking user to enter the choice
		cin >> choice1;
		// making sure that the choice is legal
		while ((choice1 != '1') && (choice1 != '2') && (choice1 != '3'))
		{
			cout << "\nEnter ERROR!\nPlease enter your option again: ";
			cin >> choice1;
		}
		// stock account
		if (choice1 == '1')
			cout << "\nStock Portfolio Accout";
		while (choice1 == '1')
		{
			cout << "\nPlease select an option:"
				<< "\n1. Display the price for a stock symbol"
				<< "\n2. Display the current portfolio"
				<< "\n3. Buy shares"
				<< "\n4. Sell shares"
				<< "\n5. View a graph for the portfolio value(please ignore)"
				<< "\n6. View transaction history"
				<< "\n7. Return to previous menu"
				<< "\nOption: ";
			cin >> choice2;
			// make sure the choice is legal
			while ((choice2 != '1') && (choice2 != '2') && (choice2 != '3')
				&& (choice2 != '4') && (choice2 != '5') && (choice2 != '6')
				&& (choice2 != '7'))
			{
				cout << "\nEnter ERROR!\nPlease enter your option again: ";
				cin >> choice2;
			}

			if (choice2 == '1')
			{
				// display the price of a stock
				stock_account.display_price();
			}
			if (choice2 == '2')
			{
				// display the current portfolio
				stock_account.display_portfolio();
			}
			if (choice2 == '3')
			{
				// buy shares
				stock_account.buy_shares();
				// set cash balance in bank account
				bank_account.set_balance();
			}
			if (choice2 == '4')
			{
				// sell shares
				stock_account.sell_shares();
				// set cash balance in bank account
				bank_account.set_balance();
			}
			/*if (choice2 == '5')
			{
				// plot a graph for the portfolio history
				stock_account.plot_graph();
			}*/
			if (choice2 == '6')
			{
				// print buy and sell transaction history
				stock_account.print_history();
			}
			// return to main menu
			if (choice2 == '7')
				break;
		}
		// bank account
		if (choice1 == '2')
			cout << "\nBank Account";
		while (choice1 == '2')
		{
			cout << "\nPlease select an option:"
				<< "\n1. View account balance"
				<< "\n2. Deposit money"
				<< "\n3. Withdraw money"
				<< "\n4. Print out history"
				<< "\n5. Return to previous menu"
				<< "\nOption: ";
			cin >> choice3;
			// make sure the choice is legal
			while ((choice3 != '1') && (choice3 != '2') && (choice3 != '3')
				&& (choice3 != '4') && (choice3 != '5'))
			{
				cout << "\nEnter ERROR!\nPlease enter your option again: ";
				cin >> choice3;
			}
			if (choice3 == '1')
			{
				// view account balance
				cout << "\nYou have $" << bank_account.get_balance()
					<< " in your bank account.";
				cout << endl;
			}
			if (choice3 == '2')
			{
				cout << "\nPlease enter the amount to deposit: ";
				cin >> deposit_value;
				// deposit money to bank account
				bank_account.deposit(deposit_value);
				cout << "\nYou have deposited $" << deposit_value
					<< " in your bank account.";
				cout << endl;
				// record cash balance
				bank_account.record_balance();
				// record deposit transaction
				bank_account.record_transaction(choice3, deposit_value);
			}
			if (choice3 == '3')
			{
				cout << "\nPlease enter the amount to withdraw: ";
				cin >> withdraw_value;
				if (bank_account.withdraw(withdraw_value))
				{
					// withdraw money from bank account
					cout << "\nYou have withdrawed $" << withdraw_value
						<< " from your bank account.\n";
					// record cash balance
					bank_account.record_balance();
					// record withdraw transaction
					bank_account.record_transaction(choice3, withdraw_value);
				}
				else
					cout << "\nTransaction failed."
					<< "\nThe balance is not sufficient to withdraw the amount.";
			}
			if (choice3 == '4')
			{
				// print deposit and withdraw history
				bank_account.print_history();
			}
			// return to main menu
			if (choice3 == '5')
				break;
		}
		// exit program
		if (choice1 == '3')
		{
			// record information in stock account
			stock_account.record_node();
			// record total portfolio
			stock_account.record_portfolio();
		}
	} while (choice1 != '3');


	system("pause");
	return 0;
}