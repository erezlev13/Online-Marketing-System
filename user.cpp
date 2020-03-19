#include "user.h"
#include <fstream>
#include <iostream>
#include <string.h>



// Constructors:

// Default constructor
User::User(const string& userName, const string& password, const Address &address) : m_address(address)
{
	setName(userName);
	setPassword(password);
}

// Destructor
User::~User()
{
	
}



// Gets
string User::getPassword()		const
{
	return m_password;
}


Address User::getAddress()	const
{
	return m_address;
}


// Sets
void User::setName(const string& userName)
{
	m_userName = userName;
}


void User::setPassword(const string& password)
{
	m_password = password;
}


void User::setAddress(const Address &address)
{
	m_address.setCity(address.getCity());
	m_address.setHouseNumber(address.getHouseNumber());
	m_address.setStreetName(address.getStreetName());
	m_address.setZip(address.getZip());
}


// Operators
ostream &operator<<(ostream &os, const User &other)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << other.m_userName;
		cout << " " << other.m_address;
	}
	else
	{
		os << "Username: " << other.m_userName;
		cout << ", Address: " << other.m_address;
	}
	return os;
}