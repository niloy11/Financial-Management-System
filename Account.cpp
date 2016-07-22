//
//	Account.cpp
//

#include "Account.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;

Account::Account()
{
	load_port();
}

void Account::load_port()
{
	double value = 0;
	string date1;
	string date2;
	string date3;
	string date4;
	string date5;

	// open portfolio_history.txt and set value to portfolio
	ifstream file;
	file.open("portfolio_history.txt");
	while (file >> value
		>> date1 >> date2 >> date3 >> date4 >> date5)
	{
		set(value);
	}
}

double Account::get()
{
	return portfolio;
}

void Account::set(double value)
{
	portfolio = value;
}