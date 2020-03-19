#pragma warning(disable:4996)
#include "order.h"
#include "product.h"
#include <iostream>
using namespace std;



// Constructor
Order::Order(vector<Product*> newOrderedProducts)
{
	m_isBuyerPaid = false;
	m_orderedProducts = newOrderedProducts;

	setTotalPrice();
}


//Destructor
Order::~Order()
{
	m_orderedProducts.clear();
}


// Gets
double Order::getTotalPrice()				const
{
	return m_totalPrice;
}


vector<Product*> Order::getOrderedProducts()	const
{
	return m_orderedProducts;
}



bool Order::getIsBuyerPaid()			const
{
	return m_isBuyerPaid;
}


// Sets
void Order::setTotalPrice()
{
	m_totalPrice = sumProductsPrices();
}


void Order::setOrderedProducts(vector<Product*> newOrderedProducts)
{
	m_orderedProducts = newOrderedProducts;
}



// Order's method
double Order::sumProductsPrices()
{
/*
Gets the array of chosen products from the buyer's order.
Then, gets the price for each product, and sum it to total price.
*/
	double totalPrice = 0;

	for (auto &temp:m_orderedProducts)
	{
		totalPrice += temp->getPrice();
		// gets and add the price of all the item in order.
	}

	return totalPrice;
}


void Order::payOrder()
{
	m_isBuyerPaid = true;
}


void Order::showOrder()	const
{
	for (auto &temp : m_orderedProducts)
	{
		cout << *temp;
		cout << endl;
	}
}