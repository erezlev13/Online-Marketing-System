#pragma warning(disable:4996)
#include "address.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// Constructors
Address::Address(const string& country, const string& cityName, const string& streetName, int houseNumber, int zip)
{
	setCountry(country);
	setCity(cityName);
	setStreetName(streetName);
	setHouseNumber(houseNumber);
	setZip(zip);
}

Address::Address(const Address &other)
{
	m_country = other.m_country;
	m_city = other.m_city;
	m_streetName = other.m_streetName;
	m_houseNumber = other.m_houseNumber;
	m_zip = other.m_zip;
}

// Move constructor
Address::Address(Address &&other)
{
	m_country = move(other.m_country);
	m_city = move(other.m_city);
	m_streetName = move(other.m_streetName);
	m_houseNumber = other.m_houseNumber;
	m_zip = other.m_zip;
}



Address::~Address()		// Destructor
{
	
}

// Gets
string Address::getCountry() const
{
	return m_country;
}

string Address::getCity()	const
{
	return m_city;
}

string Address::getStreetName()const
{
	return m_streetName;
}

int Address::getHouseNumber()const
{
	return m_houseNumber;
}

int Address::getZip()const
{
	return m_zip;
}

// Sets
bool Address::setCountry(const string& countryName)
{
	if (Validation::isValidString(countryName) == true)
	{
		m_country = countryName;
		return true;
	}
	return false;
}

bool Address::setCity(const string& cityName)// sets city. @ check about re-entering.
{
	if (Validation::isValidString(cityName) == true)
	{
		m_city = cityName;
		return true;
	}
	return false;

}

bool Address::setStreetName(const string& streetName)//sets street.
{
	if (Validation::isValidString(streetName) == true)
	{
		m_streetName =streetName;
		return true;
	}
	return false;
}

bool Address::setHouseNumber(int houseNumber)//sets house number.
{
	if (houseNumber < 1)// house can not be numbered with non-possitive number.
		return false;
	m_houseNumber = houseNumber;
	return true;
}

bool Address::setZip(int zip)
{
	if (zip < 1)// house can not be numbered with non-possitive number.
		return false;
	m_zip = zip;
	return true;
}

// Operators
std::ostream &operator<<(std::ostream &os, const Address &other)
{
	if (typeid(os) == typeid(ofstream))
	{
		os  << other.getCountry() << " " << other.getCity()
			<<  " " << other.getStreetName() << " " << other.getHouseNumber()
			<< " " << other.getZip();
	}
	else
	{
		os << "Country: " << other.getCountry() << ", " << "City: " << other.getCity() << ", "
			<< "Street: " << other.getStreetName() << ", " << "House number:" << other.getHouseNumber()
			<< ", " << "Zip: " << other.getZip();
	}
	return os;
}


