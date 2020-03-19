#ifndef __CART_H

#define __CART_H

#include "Array.h"
#include "product.h"
#include "validation.h"
#include <iostream>
#include <string.h>
using namespace std;

class Cart
{
public:
	// Constructors:
	Cart();				// Default constructor
	~Cart();			// Destructor


	// Gets
	Array<Product*> *getProducts();
	int getSize()						const;

	// Sets
	void setProducts(Array<Product*> *products);

	// Methods
	void addToCart(Product &productToAdd);
	void removeProductFromCart(int productIndex);
	void showAllProductsInCart()		const;
	double sumProductsInCartPrice();

private:
	Array<Product*> *m_products;

	Cart(const Cart &other); // Copy c'tor that we want to block.	
};

#endif // __CART_H