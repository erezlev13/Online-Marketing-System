#pragma warning(disable:4996)
#ifndef __MENU_H

#define __MENU_H

#include <string.h>
#include "system.h"
#include "buyer.h"
#include "product.h"


class Menu {
public:
	enum eMenu {
		ADD_BUYER = 1, ADD_SELLER, ADD_PRODUCT_TO_SELLER, ADD_FEEDBACK, ADD_TO_CART,
		PLACE_ORDER, PURCHASE, SHOW_BUYERS, SHOW_SELLERS, SHOW_ALL_SAME_PRODUCT, ADD_PREMIUM, SHOW_PREMIUM,
		SHOW_SAME_TYPE, OPERATOR1, OPERATOR2, OPERATOR3 ,EXIT
	};

	// Main Menu
	static void AddBuyer(System &system);
	static void AddSeller(System &system);
	static void AddProductToSellerShop(System &system);
	static void AddFeedback(System &system);
	static void AddToCart(System &system);
	static void PlaceOrder(System &system);
	static void Purchase(System &system);
	static void ShowAllBuyers(System &system);
	static void ShowAllSellers(System &system);
	static void ShowAllSameProduct(System &system);
	static void AddPremium(System &system);
	static void ShowAllPremium(System &system);
	static void ShowSameUserType(System &system);
	static void ActOperator1(System &system);	// Operator+=
	static void ActOperator2(System &system);	// Operator>
	static void ActOperator3(System &system);	// Operator<<
	static void Exit(System &system);

	// Main Methods
	static vector<Product*> makeOrderedProducts(Buyer &buyer);
	static void printMenu();
	static void cleanBuffer();

	
};

#endif // __MENU_H