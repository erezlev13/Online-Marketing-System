#pragma warning(disable:4996)
#ifndef __BUYER_H

#define __BUYER_H

#include "user.h"
#include "date.h"
#include "cart.h"
#include "order.h"
#include "validation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Seller;

class Buyer: virtual public User
{
public:
	// Constructors:
	Buyer(const string& userName, const string& password, const Address& address);	// Constructor
	Buyer(const Buyer &other) = delete;     // Copy c'tor. In order to prevent duplicate buyer.
	virtual ~Buyer();															// Destructor

	// Gets
	virtual string getName()					const override;
	Cart *getBuyerCart();	 
	vector<Order*> getBuyerOrders()				const;
	
	// Sets
	void setBuyerCart(Cart *cart);

	// Operators
	bool operator>(const Buyer &other)			const;

	// Methods
	void placeOrder(vector<Product*> orderedProducts);
	bool purchase(int numberOfOrder);
	bool giveFeedback(int serialNumber, const string& buyerFeedback, const Date &date);
	bool isAllOrdersPaid()						const;
	bool isOrderNumberExist(int orderNumber)	const;
	void showUnpaidOrders()						const;
	void showOrders()							const;

protected:
	Cart *m_cart; 
	vector<Order*> m_orders;
};




#endif // !__BUYER_H
