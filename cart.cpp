#pragma warning(disable:4996)
#include "cart.h"
#include "product.h"
#include "validation.h"
#include <iostream>
#include <string.h>
using namespace std;

// Constructors:
// Constructor
Cart::Cart()
// Initialize the products array and it's size.
{
	m_products = new Array<Product*>();
	//m_size = 0;
	//m_products = new Product*[1];//no defalut constructor hence we'll create array of pointer.
}

// Blocked copy contructor
Cart::Cart(const Cart& other) : m_products(other.m_products)
{
	//m_size = other.m_size;
	//m_products = new Product *[m_size];
	//for (int i = 0; i < m_size; i++)
	//{
		//m_products[i] = other.m_products[i];
	//}
}


//Destructor
Cart::~Cart()
{
	for (int i = 0; i < m_products->getSize(); i++)
	{
		m_products->emptyCell(i);
		delete m_products->getElement(i);
	}
	delete m_products;
}


// Gets
Array<Product*> *Cart::getProducts()
{
	return m_products;
}

int Cart::getSize()	const
{
	return m_products->getSize();
}


// Sets
void Cart::setProducts(Array<Product*> *products)
{
	/*
	Method that get the products from the user,
	by him entering the products he want to the cart.
	*/
	for (int i = 0; i < m_products->getSize(); i++)
	{
		m_products[i] = products[i];
	}
}




void Cart::addToCart(Product &productToAdd)
/*
This method gets an given and ready product, that was created in main.
Expand the cart's products arrays size, enteres the new given product and increasing the size with one.
*/
{
	if (m_products->getSize() > 0)
		m_products->modifyArray();			//Cart::modifyCart();

	m_products->addToArray(&productToAdd);  // Add the new product.
	m_products->increaseSize();				// Increases size.
}


void Cart::removeProductFromCart(int productIndex)
// Removes product from  buyer's cart.
{
	int i;
	Product *temp;
	for (i = 0; i < m_products->getSize(); i++)
	// This loop is for put nullptr in the cell that we want to remove.
	{
		if (i == productIndex)
		{
			m_products->emptyCell(i);
			break;
		}

	}

	for (int j = i; j < m_products->getSize() - 1; j++)
	{
	// Pushes the nullptr to the end.
	// Swaps
		m_products->arraySwap(j, j+1);
	}

	if (m_products->getSize() > 0) // Otherwise it is an empty cart.
		m_products->decreaseSize();	// Update the logical size after the product was removed.
}



void Cart::showAllProductsInCart()	const
{
	for (int i = 0; i < m_products->getSize(); i++)
	{
		cout << "(" << i + 1 << ")\t";
		cout <<"Name: "<< m_products->getElement(i)->getProductName() << '\t';
		cout <<"Price: "<< m_products->getElement(i)->getPrice() << '\t';
		cout <<"Serial number: "<< m_products->getElement(i)->getSerialNumber();
		cout << endl;
	}
}


double Cart::sumProductsInCartPrice()
{
/*
Gets the buyer's cart.
Then, gets the price for each product, and sum it to total price.
*/
	double totalPrice = 0;

	for (int i = 0; i < m_products->getSize(); i++)
	{
		// Gets and add the price of all the item in order.
		totalPrice += m_products->getElement(i)->getPrice();
	}

	return totalPrice;
}
