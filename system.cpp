#pragma warning(disable:4996)
#include "system.h"
#include "seller.h"
#include "buyer.h"
#include "validation.h"
#include <iostream>
#include <string.h>
using namespace std;



// Constructor
System::System()
{
	
}



// Destructor
System::~System()
{
	for (auto &temp:m_users)
		delete temp;
	m_users.clear();
}


// Gets
const string System::getSystemName()	const
{
	return m_systemName;
}

vector<User*> System::getUsers()	const
{
	return m_users;
}


// Operators
void System::operator+=(const Buyer &buyer)
{
	if (isUserRegistrated(buyer.getName()) == true)
	{
		cout << "This username is taken.\n";
	}
	else
		addUser(buyer);
}


void System::operator+=(const Seller &seller)
{
	if (isUserRegistrated(seller.getName()) == true)
	{
		cout << "This username is taken.\n";
	}
	else
		addUser(seller);
}

void System::writeToFile(ofstream &out)
{
	out << m_users.size() << endl;
	for (int i = 0; i < m_users.size(); i++)
	{
		out << typeid(*(m_users[i])).name() + 6 << " "
			<< m_users[i]->getName() << " "
			<< m_users[i]->getPassword()
			<< " " << m_users[i]->getAddress() << endl;
	}
}


void System::readFromFile(ifstream &in)
{
	int size;
	in >> size;
	for (int i = 0; i < size; i++)
	{
		string type, userName, password;
		string country, city, street;
		int houseNumber, zip;
		in >> type >> userName >> password >> country >> city >> street >> houseNumber >> zip;
		Address address(country, city, street, houseNumber, zip);
		if (type == "Buyer")
		{
			m_users.push_back(new Buyer(userName, password, address));
		}
		else if (type == "Seller")
		{
			m_users.push_back(new Seller(userName, password, address));
		}
		else
		{
			m_users.push_back(new PremiumUser(userName, password, address));
		}
	}
	in.close();
}

// Methods
bool System::isUserRegistrated(const string& userName)	const
// Method which determaine if a certain username is taken.
{
	for (auto &temp:m_users)
	{
		if (userName == temp->getName())
			return true;
	}
	return false;
}



void System::addUser(const User &user)// Or we can do: addUser(User *user)
// Gets an user from the menu and insert it to the users array with dynamic cast.
{
	const Buyer *userAsBuyer = dynamic_cast<const Buyer*>(&user);
	const Seller *userAsSeller = dynamic_cast<const Seller*>(&user);
	const PremiumUser *userAsPremium = dynamic_cast<const PremiumUser*>(&user);

	User *newUser = nullptr;
	if (userAsPremium != nullptr)
		newUser = new PremiumUser(userAsPremium->getName(), userAsPremium->getPassword(), userAsPremium->getAddress());
	else if (userAsBuyer != nullptr)
		newUser = new Buyer(userAsBuyer->getName(), userAsBuyer->getPassword(), userAsBuyer->getAddress());
	else if (userAsSeller != nullptr)
		newUser = new Seller(userAsSeller->getName(), userAsSeller->getPassword(), userAsSeller->getAddress());
	
	
	m_users.push_back(newUser);
	
}


Product *System::findProductInShops(Buyer* buyer,int productSerialNumber)	const
// Find certain product in all sellers shop.
// Return nullptr if the product dosen't exists.
{
	for (auto &user:m_users)
	{
		Buyer* userAsBuyer = dynamic_cast<Buyer*>(user);
		if (userAsBuyer == buyer) // in case buyer is also premium user.
			continue;

		Seller *userAsSeller = dynamic_cast<Seller *>(user);
		if (userAsSeller != nullptr)
		{
			for(auto &temp:userAsSeller->getShopProducts())
			{
				if (productSerialNumber == temp->getSerialNumber())
					return (temp);
			}
		}
	}
	return nullptr;
}


Product *System::findSpecificProduct(Buyer *currentBuyer, int productSerialNumber)	const
// Find certain product in all the buyer's orders.
// Returns nullptr if the product dosen't exists.
{
	for(auto &order:currentBuyer->getBuyerOrders())
	{
		for(auto &product:order->getOrderedProducts())
		{
			if (productSerialNumber == product->getSerialNumber())
			{
				// We found the specific product.
				return product;
			}
				
		}
	}
	return nullptr;
}


User *System::findUser(const string& userName)	const
// Gets the username and finds it in the users array.
{
	for (auto &user : m_users)
	{
		PremiumUser *userAsPremium = dynamic_cast<PremiumUser*>(user);
		Buyer *userAsBuyer = dynamic_cast<Buyer*>(user);
		Seller *userAsSeller = dynamic_cast<Seller*>(user);
		
		if (userAsPremium != nullptr)
		{
			if (userName == userAsPremium->getName())
			{
				return userAsPremium;
			}
		}

		else if (userAsBuyer != nullptr)
		{
			if (userName == userAsBuyer->getName())
			{
				return userAsBuyer;
			}
		}
		else if (userAsSeller != nullptr)
		{
			if (userName == userAsSeller->getName())
			{
				return userAsSeller;
			}
		}
	}
	return nullptr;
}


bool System::hasSeller()	const
{
	for (auto &temp : m_users)
	{
		Seller *user = dynamic_cast<Seller*>(temp);
	if (user != nullptr)
			return true;
	}
	return false;
}

bool System::showSameProductDetails(const string& productName)	const
// Shows all products with certain name.
{
	bool isProductExist = false;
	for (auto &temp : m_users)
	{
		Seller *userAsSeller = dynamic_cast<Seller*>(temp);
		if (userAsSeller != nullptr)
		{
			if (userAsSeller->Seller::showSameProductDetails(productName) == true)
				isProductExist = true;
		}
	}
	return isProductExist;
}


bool System::showAllSellersProducts(Buyer *buyer)	const
// Shows all products in all shops.
{
	bool isProductsExist;
	bool isStoreNotEmpty = false;
	for (auto &temp : m_users)
	{
		Buyer* userAsBuyer= dynamic_cast<Buyer*>(temp);
		if (userAsBuyer == buyer) // in case buyer is also premium user.
			continue;
		Seller *userAsSeller = dynamic_cast<Seller*>(temp);
		if (userAsSeller != nullptr)
		{
			isProductsExist = userAsSeller->Seller::showAllProducts();
			isStoreNotEmpty = (isStoreNotEmpty || isProductsExist);
		}
	}
	return isStoreNotEmpty;
}



bool System::showUsersDetails(const string& type)	const
// This method get a type to show all this user's type details.
// Shows premium users when the types 'Buyer' and 'Seller' are given.
{
	bool areUsers = false;
	for (auto &temp : m_users)
	{
		if (type == typeid(*temp).name() + 6)
		{
			cout << *(temp);
			areUsers = true;
			cout << endl;
		}
		else if (strcmp(typeid(*temp).name() + 6, "PremiumUser") == 0)
		{
			cout << *(temp);
			areUsers = true;
			cout << endl;
		}
	}
	// In case there are no users from the type that was given, we'll return false to the calling method.
	return areUsers;
}


bool System::showAllSameKindUsers(const string& type)	const
{
	if (showUsersDetails(type) == false)
		return false;
	return true;
}