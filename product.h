#pragma warning(disable:4996)
#ifndef __PRODUCT_H

#define __PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Seller;

class Product {
public:
	enum eCategory { CHILDREN, ELECTRICITY, OFFICE, CLOTHING };

	// Construcstors
	Product(const string& productName, double price, eCategory category);	// Constructor
	Product(const Product &other);											// Copy c'tor
	Product(Product &&other);												// Move constructor
	~Product();																// Destructor

	// Gets
	const string getProductName()		const;
	double getPrice()					const;
	int getSerialNumber()				const;
	eCategory getCategory()				const;
	Seller *getSeller();

	// Sets
	bool setProductName(const string& productName);
	bool setPrice(double price);
	bool setCategory(eCategory category);
	void setSeller(Seller *sellerOfProduct);

	// Operators
	friend ostream &operator<<(ostream &os, const Product &other);

	// Methods
	void printCategory(ostream &os)		const;

private:
	string m_productName;
	double m_price;
	int m_serialNumber;
	static int count;		// Help us to determine the serial number automaticly.
	eCategory m_category;
	Seller *m_seller;
};

#endif // __PRODUCT_H