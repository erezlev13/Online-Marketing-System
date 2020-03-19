#ifndef __ADDRESS_H

#define __ADDRESS_H

#include "validation.h"
#include <string>
#include <iostream>
using namespace std;

class Address
{
public:
	// Constructors:
	Address(const string& country, const string& cityName, const string& streetName, int houseNumber, int zip);
	Address(const Address &other);							// Copy c'tor
	Address(Address &&other);								// Move constructor
	~Address();												// Destructor

	// Gets
	string getCountry()		const;
	string getCity()		const;
	string getStreetName()	const;
	int getHouseNumber()	const;
	int getZip()			const;

	// Sets
	bool setCountry(const string& countryName);
	bool setCity(const string& cityName);
	bool setStreetName(const string& streetName);
	bool setHouseNumber(int houseNumber);
	bool setZip(int zip);

	// Operators
	friend ostream &operator<<(ostream &os, const Address &other);

private:
	string m_country;
	string m_city;
	string m_streetName;
	int m_houseNumber;
	int m_zip;
};





#endif // !__ADDRESS_H

