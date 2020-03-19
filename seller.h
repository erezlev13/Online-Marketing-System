#ifndef __SELLER_H

#define __SELLER_H

#include "user.h"
#include "order.h"
#include "feedback.h"
#include "product.h"
#include "validation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Seller: virtual public User
{
public:
	// Constructors:
	Seller(const string& userName, const string& password, const Address &address);	// Constructor
	Seller(const Seller &other) = delete;										// Blocked copy c'tor
	virtual ~Seller();															// Destructor

	// Gets
	virtual string getName()					const override;
	vector<Product*> getShopProducts()			const;
	vector<Feedback*> getCustomerFeedbacks()    const;

	// Sets
	void setShopProducts(vector<Product*> shopProducts);
	void setCustomerFeedbacks(vector<Feedback*> customerFeedbacks);



	// Methods
	void addProductToShop(const Product &productToAdd);
	void addFeedback(const string& buyerFeedback, const Date &date, string& buyerName, int productSerialNumber);
	bool showSameProductDetails(const string& productName)		const;
	bool showAllProducts()										const;

protected:
	vector<Product*> m_shopProducts;
	vector<Feedback*> m_customerFeedbacks;
};

#endif // __SELLER_H
