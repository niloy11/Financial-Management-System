//
//	Node.h
//	construct node to store information for stock symbol and number of stocks
//

#ifndef Node_h
#define Node_h

#include <string>
using std::string;

class Node
{
	friend class StockAccount;
public:
	Node(string& name, double number)
		:stock_symbol(name), stock_number(number)
	{
		this->left = NULL;
		this->right = NULL;
	}
private:
	string stock_symbol;
	double stock_number;
	Node *left;	// previous pointer
	Node *right;	// next pointer

};

#endif
