//
//	Account.h
//

#ifndef Account_h
#define Account_h

class Account
{
public:
	Account();
	void load_port();	// load portfolio information from text file
	void set(double);
	double get();
private:
	double portfolio;
};


#endif