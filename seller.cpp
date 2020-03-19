#pragma warning(disable:4996)
#include "seller.h"
#include "order.h"
#include "feedback.h"
#include "product.h"
#include "address.h"
#include "validation.h"
#include <iostream>
#include <string>
using namespace std;


// Constructors:
// Constructor
Seller::Seller(const string& userName, const string& password, const Address &address)
	: User(userName, password, address)
{
	
}


//Destructor
Seller::~Seller()
{
	// Delete products in shop.
	for (auto &temp : m_shopProducts)
		delete temp;
	m_shopProducts.clear();

	// Delete feedbacks
	for(auto &temp:m_customerFeedbacks)
		delete temp;
	m_customerFeedbacks.clear();
}


// Gets
string Seller::getName()			const
{
	return m_userName;
}

vector<Product*> Seller::getShopProducts()	const
{
	return m_shopProducts;
}


vector<Feedback*> Seller::getCustomerFeedbacks()	const
{
	return m_customerFeedbacks;
}


// Sets
void Seller::setCustomerFeedbacks(vector<Feedback*> customerFeedbacks)
{
	m_customerFeedbacks = customerFeedbacks;
}


void Seller::setShopProducts(vector<Product*> shopProducts)
{
	m_shopProducts = shopProducts;
}


// Methods
void Seller::addProductToShop(const Product &productToAdd)
/*
Method gets from main the given product to add to the seller's shop.
Creates new product with the given product details and insert it to the products array.
*/
{
	Product *newProduct = new Product(productToAdd);
	newProduct->setSeller(this);					// Updates the current seller of this product.
	m_shopProducts.push_back(newProduct);			// Adds the new product.
}


void Seller::addFeedback(const string& buyerFeedback, const Date &date, string& buyerName,int productSerialNumber)
// Gets the feedback details from main.
// Add the feedback to seller's feedback array.
{
	// Set the new customer feedback into the feedbacks array. 
	m_customerFeedbacks.push_back(new Feedback(buyerFeedback, date, buyerName,productSerialNumber));

}


bool Seller::showSameProductDetails(const string& productName)	const
{
	bool isProductExist = false;
	for (auto &temp:m_shopProducts)
	{
		if (temp->getProductName() == productName)
		{
			cout << *temp;
			isProductExist = true;
		}
	}
	return isProductExist;
}



bool Seller::showAllProducts()	const
{
	// If there are no products in this seller's shop.
	if (m_shopProducts.size() == 0)
		return false;
	for (auto &temp : m_shopProducts)
	{
		cout << *temp;
	}

	return true;
}
