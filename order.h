#pragma warning(disable:4996)
#ifndef __ORDER_H

#define __ORDER_H

#include "product.h"
#include <iostream>
#include <vector>
using namespace std;


class Order {
public:
	friend class buyer;

	// Constructors
	Order(vector<Product*> newOrderedProducts);	// Constructor
	~Order();								    // Detsructor

	// Gets
	double getTotalPrice()					const;
	vector<Product*> getOrderedProducts()	const;
	bool getIsBuyerPaid()					const;


	// Sets
	void setTotalPrice();
	void setOrderedProducts(vector<Product*> newOrderedProducts);

	// Order's methods
	double sumProductsPrices();
	void showOrder()				const;

	friend class Buyer;

private:
	vector<Product*> m_orderedProducts;
	double m_totalPrice;
	bool m_isBuyerPaid;

	// Private Methods
	void payOrder();

	Order(const Order &other); // Blocked copy constructor
};

#endif // __ORDER_H
