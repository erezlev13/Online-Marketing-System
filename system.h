#ifndef __SYSTEM_H

#define __SYSTEM_H


#include "premiumUser.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class System
{
public:
	// Constructors:
	System();				// Default Constructor
	~System();				// Destructor

	// Gets
	const string getSystemName()	const;
	vector<User*> getUsers()				const;
	//int getUsersSize()				const;

	// Operators
	void operator+=(const Buyer &buyer);
	void operator+=(const Seller &seller);

	// File
	void writeToFile(ofstream &out);
	void readFromFile(ifstream &in);

	// Methods
	bool isUserRegistrated(const string& userName)								const;
	void addUser(const User &user);
	Product *findProductInShops(Buyer* buyer,int productSerialNumber)			const;
	Product *findSpecificProduct(Buyer *currentBuyer, int productSerialNumber)	const;
	User *findUser(const string& userName)										const;
	bool hasSeller()															const;
	bool showAllSellersProducts(Buyer* buyer)									const;
	bool showSameProductDetails(const string& productName)						const;
	bool showUsersDetails(const string& type)									const;
	bool showAllSameKindUsers(const string& type)								const;

private:
	const string m_systemName="System";
	vector<User*> m_users;
	System(const System &other); // Blocked copy c'tor.
};

#endif // __SYSTEM_H
