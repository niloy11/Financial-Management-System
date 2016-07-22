//
//	StockAccount.h
//

#ifndef StockAccount_h
#define StockAccount_h

#include "Account.h"
#include <iostream>
#include "Node.h"
#include <string>

using std::string;

class StockAccount :public Account
{
public:
	StockAccount();
	int size() const;	// size of doubly linked list

	void display_price();
	void display_portfolio();
	void buy_shares();
	void sell_shares();
	//void plot_graph();

	// add stock to doubly linked list when buy shares
	void add_stock(Node *, string, double);

	// delete stock from doubly linked list when sell shares
	bool remove_from_start();
	bool remove_from_end();

	// record buy and sell transaction history
	void record(char, string, double, double);

	// record node information
	void record_node();

	// record portfolio
	void record_portfolio();
	
	// print buy and sell transaction history
	void print_history();

private:
	Node *myHead;
	Node *myTail;
	int mysize;
};



#endif