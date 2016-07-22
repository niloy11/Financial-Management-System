//
//	StockAccount.cpp
//

#define _CRT_SECURE_NO_WARNINGS
/*#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include "mex.h" */

#include "StockAccount.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <new>
#include "Node.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::setw;
using std::ios;
using std::vector;
using namespace std;

//#include <engine.h>


StockAccount::StockAccount()
:Account(), myHead(0), myTail(0)
{
	string symbol;
	double number;

	// read stock information from stock_account.txt
	// and put them in nodes and links
	ifstream file5("stock_account.txt", ios::in);
	while (file5 >> symbol >> number)
	{
		add_stock(new Node(symbol, number), symbol, number);
	}
}

// size of doubly linked list
int StockAccount::size() const
{
	return mysize;
}

// add stock to doubly linked list when buy shares
void StockAccount::add_stock(Node *newvalue, string stocksymbol, double stocknumber)
{
	int flag = 0;
	if (size() == 0)
	{
		// add new node to head or tail
		myHead = myTail = newvalue;
		mysize++;
	}
	else
	{
		// add stock number if first node is the one that client buys
		if (myHead->stock_symbol == stocksymbol)
			myHead->stock_number += stocknumber;

		// add stock number if last node is the one that client buys
		else if (myTail->stock_symbol == stocksymbol)
			myTail->stock_number += stocknumber;

		else
		{
			Node *current = myHead;
			while (current != myTail)
			{
				// add stock number when find a node is the one client buys
				if (current->stock_symbol == stocksymbol)
				{
					current->stock_number += stocknumber;
					flag = 1;
				}
				current = current->right;
			}

			// new stock, add new node to end of linked list
			if (flag == 0)
			{
				myTail->right = newvalue;
				myTail = newvalue;
				myTail->left = current;
				mysize++;
			}
		}
	}

}

// delete stock from start of doubly linked list when sell shares
bool StockAccount::remove_from_start()
{

	if (size() == 0)
		return false;
	else{

		Node *temp = myHead;
		if (myHead == myTail)
			myHead = myTail = 0;
		else
		{
			myHead = myHead->right;
			myHead->left = 0;
		}
		delete temp;
		mysize--;

		return true;
	}

}

// delete stock from end of doubly linked list when sell shares
bool StockAccount::remove_from_end()
{
	if (size() == 0)
		return false;
	else{

		Node *temp = myTail;
		if (myHead == myTail)
			myHead = myTail = 0;
		else
		{
			myTail = myTail->left;
			myTail->right = 0;
		}
		delete temp;
		mysize--;

		return true;
	}
}

// display the price of a stock
void StockAccount::display_price()
{
	string symbol;
	int judge = 0;
	cout << "\nPlease enter the stock symbol: ";
	cin >> symbol;

	ifstream result;

	string saved_symbol;
	double saved_price;
	string saved_time;

	// read file randomly
	int seed = rand() % 2;
	if (seed == 0)
	{
		result.open("Results_1.txt");
	}
	if (seed == 1)
	{
		result.open("Results_2.txt");
	}

	for (int i = 0; i < 49; i++)
	{
		result >> saved_symbol >> saved_price >> saved_time;
		// compare symbol, if same, print out
		if (symbol == saved_symbol)
		{
			cout << "\nCompany Symbol     Price per share\n";
			cout << setw(8) << saved_symbol << setw(22) << saved_price;
			judge = 1;
		}
	}
	// not finding same symbol
	if (judge == 0)
	{
		cout << "\nSymbol cannot be found.";
	}
	cout << endl;
}

// display the current portfolio
void StockAccount::display_portfolio()
{
	if (size() == 0)
	{
		cout << "\nThere is no stock in your account.\n";
		return;
	}

	Node *current = myHead;
	double total_value = 0;
	double total_portfolio = 0;
	double balance = 0;
	//int judge = 0;

	string saved_symbol;
	double saved_price;
	string saved_time;

	// read cash balance value
	ifstream file1("cash_history.txt");
	if (file1.is_open() == false)
	{
		balance = 10000;
	}
	else
	{
		file1 >> balance;
	}
	cout << "\nCash balance = $" << balance << endl;

	ifstream result;
	int seed = rand() % 2;
	cout << seed << endl;
	cout << "Company Symbol     Number"
		<< "     Price per share     Total Value\n";

	// compare symbol in node with symbol in files,
	// if same, print information and calculate
	// total portfolio
	while (current != 0)
	{
		if (seed == 0)
		{
			result.open("Results_1.txt");
		}
		if (seed == 1)
		{
			result.open("Results_2.txt");
		}
		for (int i = 0; i < 49; i++)
		{
			result >> saved_symbol >> saved_price >> saved_time;
			// compare symbols
			if (current->stock_symbol == saved_symbol)
			{
				total_value = (current->stock_number)*saved_price;
				cout << setw(8) << saved_symbol
					<< setw(16) << current->stock_number
					<< setw(16) << saved_price
					<< setw(12) << "$" << total_value;
				cout << endl;
				total_portfolio += total_value;
			}
		}
		result.close();
		current = current->right;	// next node
	}
	total_portfolio += balance;		// total portfolio
	cout << "Total portfolio value: $" << total_portfolio;
	set(total_portfolio);
	cout << endl;
}

// buy shares
void StockAccount::buy_shares()
{
	string symbol;
	double number = 0;
	double maximum = 0;
	char choice = '3';
	int judge = 0;
	double balance = 0;

	// read cash balance value
	ifstream file1("cash_history.txt");
	if (file1.is_open() == false)
	{
		balance = 10000;
	}
	else
	{
		file1 >> balance;
	}

	cout << "\nPlease enter the stock symbol you wish to purchase: ";
	cin >> symbol;

	ifstream result;
	int seed = rand() % 2;
	if (seed == 0)
	{
		result.open("Results_1.txt");
	}
	if (seed == 1)
	{
		result.open("Results_2.txt");
	}

	string saved_symbol;
	double saved_price;
	string saved_time;

	// compare symbol, if same, prepare to buy
	for (int i = 0; i < 49; i++)
	{
		result >> saved_symbol >> saved_price >> saved_time;
		if (symbol == saved_symbol)
		{
			cout << "\nPlease enter the number of shares: ";
			cin >> number;

			// shares value are too high
			if (saved_price * number > balance)
			{
				cout << "\nTransaction failed: cash balance is not enough.";
			}
			else
			{
				cout << "\nPlease enter the maximum amount you are willing to pay per share: ";
				cin >> maximum;
				// maximum price is not enough
				if (saved_price > maximum)
				{
					cout << "\nTransaction failed: maximum amount is not enough.";
				}
				// buy stock
				else
				{
					balance -= saved_price * number;

					// record cash balance
					ofstream history;
					history.open("cash_history.txt");
					history << balance;

					cout << "\nYou have purchased " << number << " shares of " << symbol
						<< " at $" << saved_price
						<< " each for a total of $" << number*saved_price;
					cout << endl;

					// record transaction history
					record(choice, symbol, number, saved_price);

					// add stock information to linked list
					add_stock(new Node(symbol, number), symbol, number);
				}
			}
			judge = 1;
		}
	}
	// cannot find stock
	if (judge == 0)
	{
		cout << "\nTransaction failed: cannot find stock symbol.";
	}

}

// sell shares
void StockAccount::sell_shares()
{
	string symbol;
	double number = 0;
	double minimum = 0;
	char choice = '4';
	//int judge = 0;
	double balance = 0;

	// read cash balance from cash_history.txt
	ifstream file1("cash_history.txt");
	if (file1.is_open() == false)
	{
		balance = 10000;
	}
	else
	{
		file1 >> balance;
	}

	// nothing in stock account, cannot sell any stock
	if (size() == 0)
	{
		cout << "\nTransaction failed: nothing is in your account.\n";
	}
	else
	{
		cout << "\nPlease enter the stock symbol that you want to sell: ";
		cin >> symbol;
		Node *current = myHead;

		// find the symbol client want to sell
		while (current != 0)
		{
			if (current->stock_symbol == symbol)
				break;
			current = current->right;
		}

		// not find, cannot sell
		if (current == 0)
		{
			cout << "\nTransaction failed: cannot find "
				<< symbol << " in your account.";
		}
		// find, prepare to sell
		else
		{
			cout << "\nPlease enter the number of shares you want to sell: ";
			cin >> number;

			// sell too many
			if (number > current->stock_number)
			{
				cout << "\nTransaction failed: stock number in the account is not enough.";
			}
			else
			{
				// open file randomly
				ifstream result;
				int seed = rand() % 2;
				if (seed == 0)
				{
					result.open("Results_1.txt");
				}
				if (seed == 1)
				{
					result.open("Results_2.txt");
				}

				string saved_symbol;
				double saved_price;
				string saved_time;

				for (int i = 0; i < 49; i++)
				{
					result >> saved_symbol >> saved_price >> saved_time;
					if (symbol == saved_symbol)
					{
						cout << "\nPlease enter the minimum amount you are willing to spend per share: ";
						cin >> minimum;
						// selling price is too high
						if (minimum >saved_price)
						{
							cout << "\nTransaction failed: minimum amount is too high.";
						}
						// sell shares
						else
						{
							// all shares sold out, delete node from doubly linked list
							if (number == current->stock_number)
							{
								if (current == myHead)
									remove_from_start();
								else if (current == myTail)
									remove_from_end();
								else
								{
									Node *temp;
									temp = current;
									current->left->right = current->right;
									current->right->left = current->left;
									delete temp;
									mysize--;
								}
							}
							// if number of stocks is not zero then change the number of stocks
							else
							{
								current->stock_number -= number;
							}

							cout << "\nYou have sold " << number << " shares of "
								<< symbol << " at $" << saved_price
								<< " each for a total of $" << number*saved_price;
							balance += (number*saved_price);
							// record transaction history
							record(choice, symbol, number, saved_price);
							// record cash balance
							ofstream history;
							history.open("cash_history.txt");
							history << balance;
						}
					}
				}
			}
		}
	}
}

// plot graph of portfolio
/*void StockAccount::plot_graph()
{

	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found"
			<< endl;
		exit(1);
	}

	vector< double > port;
	double value = 0;
	string date1;
	string date2;
	string date3;
	string date4;
	string date5;

	ifstream file;
	file.open("portfolio_history.txt");

	while (file >> value
		>> date1 >> date2 >> date3 >> date4 >> date5)
	{
		port.push_back(value);
	}

	double *portvalue = new double[port.size()];
	for (int i = 0; i < port.size(); i++)
	{
		portvalue[i] = port[i];
	}
	
	mxArray *A;
	// assume A gets initialized, all values
	A = mxCreateDoubleMatrix(1, port.size(), mxREAL);
	memcpy((void *)mxGetPr(A), (void *)portvalue, sizeof(double)* port.size());
	engPutVariable(ep, "portvalue", A);

	engEvalString(ep, "plot(portvalue,'--o');");
	engEvalString(ep, "xlabel('number');");
	engEvalString(ep, "ylabel('Portfolio');");
	engEvalString(ep, "title('Trend of Portfolio')");

}*/

// record buy and sell transaction history
void StockAccount::record(char choice, string stock_symbol,
	double amount, double price)
{
	time_t moment;
	moment = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&moment);

	ofstream transaction;
	transaction.open("stock_transaction_history.txt", ios::app);
	transaction << ((choice == '3') ? "Buy" : "Sell")
		<< "   " << stock_symbol << "   " << amount
		<< "   $" << price << "   $" << amount*price
		<< "   " << asctime(timeinfo);
	transaction.close();
}

// record node information
void StockAccount::record_node()
{
	Node *current = myHead;
	ofstream node_content;
	if (size() != 0)
	{
		node_content.open("stock_account.txt");

		while (current != 0)
		{
			node_content << current->stock_symbol << "   " << current->stock_number << endl;
			current = current->right;
		}
	}
	else
		node_content.open("stock_account.txt");
	node_content.close();
}

// record portfolio value
void StockAccount::record_portfolio()
{
	time_t moment;
	moment = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&moment);

	if (size() == 0)
	{
		cout << "\nThere is no stock in your account.\n";
		ofstream port;
		port.open("portfolio_history.txt", ios::app);
		port << get() << "   " << asctime(timeinfo);
		port.close();
		return;
	}

	Node *current = myHead;
	double total_value = 0;
	double total_portfolio = 0;
	double balance = 0;
	//int judge = 0;

	string saved_symbol;
	double saved_price;
	string saved_time;
	// read cash balance value
	ifstream file1("cash_history.txt");
	if (file1.is_open() == false)
	{
		balance = 10000;
	}
	else
	{
		file1 >> balance;
	}
	
	ifstream result;
	srand(time(0));
	int seed = rand() % 2;
	while (current != 0)
	{
		if (seed == 0)
		{
			result.open("Results_1.txt");
		}
		if (seed == 1)
		{
			result.open("Results_2.txt");
		}
		// calculate total portfolio
		for (int i = 0; i < 49; i++)
		{
			result >> saved_symbol >> saved_price >> saved_time;
			if (current->stock_symbol == saved_symbol)
			{
				total_value = (current->stock_number)*saved_price;
				total_portfolio += total_value;
			}
		}
		result.close();
		current = current->right;
	}
	total_portfolio += balance;
	set(total_portfolio);

	ofstream port;
	port.open("portfolio_history.txt", ios::app);
	port << total_portfolio << "   " << asctime(timeinfo);
	port.close();
}

// print buy and sell transaction history
void StockAccount::print_history()
{
	string manipulate;
	string symbol;
	string number;
	string price;
	string total_price;

	string date1;
	string date2;
	string date3;
	string date4;
	string date5;

	ifstream file3("stock_transaction_history.txt", ios::in);
	while (file3 >> manipulate >> symbol >> number >> price >> total_price
		>> date1 >> date2 >> date3 >> date4 >> date5)
	{
		cout << setw(4) << manipulate << setw(6) << symbol
			<< setw(6) << number << setw(10) << price
			<< setw(10) << total_price << setw(5)
			<< date1 << setw(5) << date2 << setw(4)
			<< date3 << setw(10) << date4 << setw(6) << date5;
		cout << endl;
	}
}
