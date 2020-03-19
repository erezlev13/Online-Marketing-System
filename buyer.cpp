#pragma warning(disable:4996)
#include "buyer.h"
#include "order.h"
#include "address.h"
#include "date.h"
#include "cart.h"
#include "seller.h"
#include "validation.h"
#include <iostream>
#include <string.h>
using namespace std;


// Constructors
// Add const to the variable sent to the constructors because we don't want to change them.
Buyer::Buyer(const string& userName, const string& password, const Address &address)
	: User(userName, password, address)
{
	m_cart = new Cart();
	//m_orders = new Order*[1];
	//m_ordersSize = 0;
}


// Destructor
Buyer::~Buyer()
{
	for(auto &temp:m_orders)
		delete temp;
	m_orders.clear();//delete[] m_orders;
	delete m_cart;
}


// Gets
string Buyer::getName()			const
{
	return m_userName;
}

Cart *Buyer::getBuyerCart()
{
	return m_cart;
}

vector<Order*> Buyer::getBuyerOrders() const
{
	return m_orders;
}


// Sets
void Buyer::setBuyerCart(Cart *cart)
{
	m_cart->setProducts(cart->getProducts());
}


// Operators
bool Buyer::operator>(const Buyer &other)	const
{
	if (this->m_cart->sumProductsInCartPrice() > other.m_cart->sumProductsInCartPrice())
		return true;
	return false;
}

// Methods
void Buyer::placeOrder(vector<Product*> orderedProducts)
{
/*
This Method gets the ordered products from the Menu in Place Order act.
Creates a new order with the given products array, and insert the new order to the buyer's order array.
Also, increasing the size of the order array with one after the new order is entered.
*/
	if (orderedProducts.size() != 0)
	// If the user stopped making an order before adding one product (entered 0),
	// in the first time of entering an product number.
	{

		// Put in the orders array, the products which chosen to be ordered.
		Order *order;
		order = new Order(orderedProducts);
		m_orders.push_back(order);
	}
}



bool Buyer::purchase(int numberOfOrder)
/* 
Get the order number from user. Removes all the products from the seller's shops,
*/
{
	if (numberOfOrder >= 0 && numberOfOrder < m_orders.size())
	// If the user inserted an index which is compatible with the array size.
	{
		for (int i = 0; i < m_orders.size(); i++)
		{
			if (numberOfOrder == i && m_orders[numberOfOrder]->getIsBuyerPaid() == false)
			// If the order's index exist and is not already paid for.
			{
				m_orders[i]->payOrder();	// Change the payment status of the buyer's order.
				return true;
			}
		}
	}
	return false;
}


bool Buyer::giveFeedback(int serialNumber, const string& buyerFeedback, const Date &date)
/*
This method gets the given product's serial number to give a feedback on.
Also, it gets the buyer's feedback with the given date.
It goes to the match seller of the given product and send the details to the Seller's method(addFeedack).
Also, it returns true or false if the given product is exist.
*/
{
	//for (int i = m_orders.size() - 1; i >= 0; i--)
	for(auto &temp:m_orders)
	// More likely that the buyer will give a feedback to the recent product he bought.
	{
		for (int j = 0; j < temp->getOrderedProducts().size(); j++)
		{
		// Reach the specific product of the specific order,
		// which the buyer decided to give a feedback on (to the specific seller).
			if (serialNumber == temp->getOrderedProducts()[j]->getSerialNumber())
			// Finds the match product with the product's serial number.
			{
				temp->getOrderedProducts()[j]->getSeller()->addFeedback(buyerFeedback, date, m_userName,serialNumber);
				return true;
			}
		}
	}
	// If there is no product with this serial number in the orders.
	return false;
}


bool Buyer::isAllOrdersPaid()	const
{
	for (auto &temp : m_orders)
	{
		if (temp->getIsBuyerPaid() == false)
			return false;
	}
	return true;
}


bool Buyer::isOrderNumberExist(int orderNumber)	const
{
	for (int i = 0; i < m_orders.size(); i++)
	{
		if (orderNumber == i)
			return true;
	}
	return false;
}



void Buyer::showUnpaidOrders()	const
// Shows all unpaid orders from the orders array of this buyer.
{
	for (int i = 0; i < m_orders.size(); i++)
	{
		if (m_orders[i]->getIsBuyerPaid() == false)
		{
			cout << "Order Number  " << i << endl;
			m_orders[i]->showOrder();
			cout << endl;
		}

	}
}

void Buyer::showOrders()	const
// Shows all orders in general of this buyer.
{
	for (int i = 0; i < m_orders.size(); i++)
	{

		cout << "Order Number  " << i << endl;
		m_orders[i]->showOrder();
		cout << endl;
	}
}
