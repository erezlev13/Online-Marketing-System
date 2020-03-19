#pragma warning(disable:4996)
#include "product.h"
#include "seller.h"
#include "validation.h"
#include <iostream>
#include <string.h>
using namespace std;

int Product::count = 0;

// Construcstors
// Constructor
Product::Product(const string& productName, double price, eCategory category) : m_seller(nullptr)
{
	setPrice(price);
	m_serialNumber = ++count;
	setCategory(category);
	setProductName(productName);
}

Product::Product(const Product &other)
{
	m_price = other.m_price;
	m_category = other.m_category;
	m_serialNumber = other.m_serialNumber;
	m_productName = other.m_productName;
}

// Move constructor
Product::Product(Product &&other) : m_productName(nullptr), m_seller(nullptr)
{
	m_price = other.m_price;
	m_category = other.m_category;
	m_serialNumber = other.m_serialNumber;
	m_productName = move(other.m_productName);
}



// Destructor
Product::~Product()
{
	
}


// Gets
const string Product::getProductName()const
{
	return m_productName;
}


double Product::getPrice()const
{
	return m_price;
}


int Product::getSerialNumber()const
{
	return m_serialNumber;
}


Product::eCategory Product::getCategory()const
{
	return m_category;
}


Seller *Product::getSeller()
{
	return m_seller;
}


// Sets
bool Product::setProductName(const string& productName)
{
	if (productName.length() != 0)
	// check if the name isn't empty
	{
		m_productName = productName;
		return true;
	}
	return false;
}


bool Product::setPrice(double price)
{
	if (price >= 0)
		// check if the price is a real-positive number
	{
		m_price = price;
		return true;
	}
	return false;
}


bool Product::setCategory(eCategory category)
{
	if (category >= 0 && category <= 3)
	// Checks if the category is one of the four: children, office, clothing and electricity.
	{
		m_category = category;
		return true;
	}
	return false;
}


void Product::setSeller(Seller *sellerOfProduct)
{
	m_seller = sellerOfProduct;
}

// Operators
ostream &operator<<(ostream &os, const Product &other)
{
	os << "Name: " << other.m_productName <<'\t';
	os << "Category: ";
	other.printCategory(os);
	os << '\t';
	os << "Price: " << other.m_price << '\t';
	os << "Serial number: " << other.m_serialNumber << endl;
	return os;
}


void Product::printCategory(ostream &os)	const
{
	if (m_category == (eCategory)CHILDREN)
		os << "Children";
	else if (m_category == (eCategory)ELECTRICITY)
		os << "Electricity";
	else if (m_category == (eCategory)OFFICE)
		os << "Office";
	else
		os << "Clothing";
}