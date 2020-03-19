#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "menu.h"
using namespace std;




int main()
{
	int actNumber;
	ifstream file("systemData.txt");
	System system;
	if (file.is_open() == true)
		system.readFromFile(file);



	Menu::printMenu();	// Show the menu options.

	// The user choose an action from the menu.
	cout << "Please choose an action: ";
	cin >> actNumber;

	while (actNumber != Menu::EXIT)
	{
		switch (actNumber)
		{
			// Add buyer action.
		case Menu::ADD_BUYER:
		{
			Menu::AddBuyer(system);
			break;
		}

		// Add seller action.
		case Menu::ADD_SELLER:
		{
			Menu::AddSeller(system);
			break;
		}

		// Add product to seller's shop.
		case Menu::ADD_PRODUCT_TO_SELLER:
		{
			Menu::AddProductToSellerShop(system);
			break;
		}

		// Add feedback to buyer's product.
		case Menu::ADD_FEEDBACK:
		{
			Menu::AddFeedback(system);
			break;
		}

		// Add product to the buyer's cart.
		case Menu::ADD_TO_CART:
		{
			Menu::AddToCart(system);
			break;
		}

		// Buyer's place order action.
		case Menu::PLACE_ORDER:
		{
			Menu::PlaceOrder(system);
			break;
		}

		// Buyer's purchase specific order action.
		case Menu::PURCHASE:
		{
			Menu::Purchase(system);
			break;
		}

		case Menu::SHOW_BUYERS:
		{
			Menu::ShowAllBuyers(system);
			break;
		}

		case Menu::SHOW_SELLERS:
		{
			Menu::ShowAllSellers(system);
			break;
		}

		case Menu::SHOW_ALL_SAME_PRODUCT:
		{
			Menu::ShowAllSameProduct(system);
			break;
		}

		case Menu::ADD_PREMIUM:
		{
			Menu::AddPremium(system);
			break;
		}

		case Menu::SHOW_PREMIUM:
		{
			Menu::ShowAllPremium(system);
			break;
		}

		case Menu::SHOW_SAME_TYPE:
		{
			Menu::ShowSameUserType(system);
			break;
		}

		case Menu::OPERATOR1:
		{
			Menu::ActOperator1(system);
			break;
		}

		case Menu::OPERATOR2:
		{
			Menu::ActOperator2(system);
			break;
		}

		case Menu::OPERATOR3:
		{
			Menu::ActOperator3(system);
			break;
		}

		default:
			// In case that the user entered invalid action number. For example: The user entered 12.
			cout << "Illeagel action. Please enter a number between 1-17 to choose an action." << endl;
			break;
		}

		cout << endl;
		Menu::printMenu();	// Show the menu options.
		cout << endl;

		// The user choose an action from the menu.
		cout << "Please choose an action: ";
		cin >> actNumber;

		if (actNumber == Menu::EXIT)
		{
			Menu::Exit(system);
		}
	}


	return 0;
}

