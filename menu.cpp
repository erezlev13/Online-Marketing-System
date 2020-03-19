#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <string>
#include "menu.h"
using namespace std;



// Main Menu
void Menu::AddBuyer(System &system)
{
	bool isUserNameTaken = false;
	string userName, password;
	string country, city, street;
	int houseNumber, zip;

	cout << "Please enter your username: ";
	cin >> userName;
	while (system.isUserRegistrated(userName) == true)
	{
		cout << "This username is taken.\nPlease enter a new username:";
		cin >> userName;
	}
	cout << "Please enter your password: ";
	cin >> password;
	cout << endl;
	cout << "Please enter your address: " << endl;
	cleanBuffer();
	cout << "Country: ";
	getline(cin, country);
	cout << "City: ";
	getline(cin , city);
	cout << "Street: ";
	getline(cin , street);
	cout << "House Number: ";
	cin >> houseNumber;
	cout << "Zip code: ";
	cin >> zip;
	
	Address address(country, city, street, houseNumber, zip);
	Buyer buyer(userName, password, address);
	system.addUser(buyer);
	cout << endl;
	cout << userName << " was added as a buyer to the system." << endl;
	
}



void Menu::AddSeller(System &system)
{
	string userName, password;
	string country, city, street;
	int houseNumber, zip;

	cout << "Please enter your username: ";
	cin >> userName;
	cleanBuffer();
	while (system.isUserRegistrated(userName) == true)
	{
		cout << "This username is taken.\nPlease enter a new username: " ;
		cin >> userName;
		cleanBuffer();
	}
	cout << "Please enter your password: ";
	cin >> password;
	cout << endl;
	cout << "Please enter your address: " << endl;
	cleanBuffer();
	cout << "Country: ";
	getline(cin, country);
	cout << "City: ";
	getline(cin, city);
	cout << "Street: ";
	getline(cin, street);
	cout << "House Number: ";
	cin >> houseNumber;
	cout << "Zip code: ";
	cin >> zip;
	
	Address address(country, city, street, houseNumber, zip);
	Seller seller(userName, password, address);
	system.addUser(seller);
	cout << endl;
	cout << userName << " was added as a seller to the system." << endl;
}


void Menu::AddProductToSellerShop(System &system)
{
	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	Seller *sellerPtr = dynamic_cast<Seller*>(system.findUser(userName));

	if (sellerPtr != nullptr)
	{
		string productName;
		double price;
		int category;
		cout << "Please enter the product details, that you want to add: " << endl;
		cout << "Product name: ";
		cin >> productName;
		cout << "Price: ";
		cin >> price;
		if (price <= 0)
		{
			cout << "Product's price should be a positive number only.\n";
			return;
		}
		cout << "Enter Category. 0 for children, 1 for electricity,";
		cout << " 2 for office, 3 for clothing: ";
		cin >> category;
		while (category < 0 || category>3)
		{
			cout << "Enter Category. 0 for children, 1 for electricity,";
			cout << " 2 for office, 3 for clothing: ";
			cin >> category;
		}
		Product product(productName, price, (Product::eCategory)category);
		sellerPtr->addProductToShop(product);
	}
	else
	{
		cout << "There is no seller with this username.\n";
	}

}


void Menu::AddFeedback(System &system)
{
	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	Buyer *buyerPtr = dynamic_cast<Buyer*>(system.findUser(userName));

	if (buyerPtr != nullptr)
	// If the buyer logged in successfully.
	{
		if (buyerPtr->getBuyerOrders().size() == 0)
			// If there no orders for this buyer.
			cout << "There are no orders for this buyer.\n";

		else
		{
			// If there is at least one order in the order list.
			cout << "Please enter the product's serial number from the given product list:\n";
			buyerPtr->showOrders();


			// The buyer can choose a specific product to give a feedback on.
			int chosenProductSerialNumber;
			cout << "Chosen product's serial number: ";
			cin >> chosenProductSerialNumber;

			if (system.findSpecificProduct(buyerPtr,chosenProductSerialNumber) == nullptr)
				cout << "This buyer has no product ordered with this serial number.\n";
			else
			{
				string feedBackBody;
				int day, month, year;
				cleanBuffer();
				cout << "Please enter your feedback:" << endl;
				getline(cin , feedBackBody);
				cout << "Please enter the date:\nDay: ";
				cin >> day;
				cout << "Month: ";
				cin >> month;
				cout << "Year: ";
				cin >> year;
				Date feedbackDate(day, month, year);

				buyerPtr->giveFeedback(chosenProductSerialNumber, feedBackBody, feedbackDate);
				cout << "Thank you for your feedback, ";
				cout << "your feedback was added to the seller." << endl;
			}
		}
	}
	else
	{
		cout << "There is no buyer with this username." << endl;
	}
}



void Menu::AddToCart(System &system)
{
	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	Buyer *buyerPtr = dynamic_cast<Buyer*>(system.findUser(userName));

	if (buyerPtr != nullptr)
	// If the buyer logged in successfully.
	{
		if (system.hasSeller() == false)
		// If there no sellers in the system's users array.
			cout << "There are no sellers at the moment.\n";
		else if (system.showAllSellersProducts(buyerPtr) == false)
		// If there are no products at all in all the seller's shops.
			cout << "There are no products in all seller's shops.\n";
		else {
		// There is at least one product on at least one shop of one of the sellers.
			cout << "Please choose the product you want to add to your cart: \n";
			cout << "Please enter the product's serial number: ";
			int productSerialNumber;
			cin >> productSerialNumber;
			Product *productToAdd = system.findProductInShops(buyerPtr,productSerialNumber);
			if (productToAdd == nullptr)
			{
				cout << "There is no product exists with this serial number in the shops.\n";
			}
			else
			{
				buyerPtr->getBuyerCart()->addToCart(*productToAdd);
				cout << productToAdd->getProductName() << " was added to your cart.\n";
			}
		}
	}
	else
	{
		cout << "There is no buyer with this username." << endl;
	}
	
}


void Menu::PlaceOrder(System &system)
{
	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	Buyer *buyerPtr = dynamic_cast<Buyer*>(system.findUser(userName));
	vector<Product*> orderedProducts;
	
	if (buyerPtr != nullptr) // If the buyer logged in successfully.
	{
		//if the buyer's cart is empty we don't create an order and send him a message(in makeOrderedProducts).
		orderedProducts = makeOrderedProducts(*buyerPtr);
		if (orderedProducts.size() != 0)
		{
			buyerPtr->placeOrder(orderedProducts);
			if (orderedProducts.size() != 0)
				cout << "Thank you for placing an order.\n";
			else
			// If the user stopped the order before he added one product.
				cout << "You finished the order before adding a product.\n";
		}

	}
	else
	// The user(buyer) didn't succeed to logged in.
	{
		cout << "There is no buyer with this username." << endl;
	}
}


void Menu::Purchase(System &system)
{
	string userName;
	cout << "Please enter your username: ";
	cin >> userName;
	Buyer *buyerPtr = dynamic_cast<Buyer*>(system.findUser(userName));
	if (buyerPtr != nullptr)
	{
		if (buyerPtr->getBuyerOrders().size() == 0)
			cout << "There are no orders for this buyer.\n";
		else if (buyerPtr->isAllOrdersPaid() == true)
			cout << "All orders is already paid by this buyer.\n";
		else
		{
			int orderNumber;
			buyerPtr->showUnpaidOrders();
			cout << "Please enter the number of the order you want to purchase: ";
			cin >> orderNumber;
			if (buyerPtr->purchase(orderNumber) == false)
				cout << "There is no order with this number.\n";
			else
				cout << "Thank you for purchasing the order.\n";
		}
	}

	else
	// The user(buyer) didn't succeed to logged in.
	{
		cout << "There is no buyer with this username." << endl;
	}
}



void Menu::ShowAllBuyers(System &system)
{
	if (system.showUsersDetails("Buyer") == false)
		cout << "There are no buyers at the moment.\n";
	
}


void Menu::ShowAllSellers(System &system)
{
	if(system.showUsersDetails("Seller") ==false)
		cout << "There are no sellers at the moment.\n";
}


void Menu::ShowAllSameProduct(System &system)
{
	string productName;
	cout << "Please enter the product's name:" << endl;
	cin >> productName;
	if (system.showSameProductDetails(productName) == false)
		cout << "There is no such product with this name." << endl;
}


void Menu::AddPremium(System &system)
{
	bool isUserNameTaken = false;
	string userName, password;
	string country, city, street;
	int houseNumber, zip;

	cout << "Please enter your username: ";
	cin >> userName;
	while (system.isUserRegistrated(userName) == true)
	{
		cout << "This username is taken.\nPlease enter a new username:";
		cin >> userName;
	}
	cout << "Please enter your password: ";
	cin >> password;
	cout << endl;
	cleanBuffer();
	cout << "Please enter your address: " << endl;
	cout << "Country: ";
	getline(cin, country);
	cout << "City: ";
	getline(cin, city);
	cout << "Street: ";
	getline(cin, street);
	cout << "House Number: ";
	cin >> houseNumber;
	cout << "Zip code: ";
	cin >> zip;

	Address address(country, city, street, houseNumber, zip);
	PremiumUser premium(userName, password, address);
	system.addUser(premium);
	cout << endl;
	cout << userName << " was added as a premium to the system." << endl;
}


void Menu::ShowAllPremium(System &system)
{
	if (system.showUsersDetails("PremiumUser") == false)
		cout << "There are no premium users at the moment.\n";
}


void Menu::ShowSameUserType(System &system)
{
	int chosenNumber;
	string type;
	cout << "Please enter the number of the type you would like to see:\n";
	cout << "1. Buyer\n";
	cout << "2. Seller\n";
	cout << "3. Buyer-Seller(Premium)\n";
	cout << "Please enter the number: ";
	cin >> chosenNumber;

	while (chosenNumber < 1 || chosenNumber > 3)
	{
		cout << "The number has to be between 1 to 3 only. Please enter a number again:\n";
		cout << "Please enter the number: ";
		cin >> chosenNumber;
	}

	if (chosenNumber == 1)
	{
		type = "Buyer";
	}
	else if (chosenNumber == 2)
	{
		type ="Seller";
	}
	else
		type  = "PremiumUser";
	cout << endl;
	if (system.showAllSameKindUsers(type) == false)
		cout << "There are no users from  "<< type <<" at this moment\n";
}


// Operator+=
void Menu::ActOperator1(System &system)
{
	Address address1("Israel", "Even-Yehuda", "HayeletHashahar", 12, 40500);
	Buyer buyer("erezlev13", "123", address1);

	// Operator+=:
	// Add buyer
	cout << "The buyer that is need to be added is: " << buyer.getName(); // We used Operator<< here, in the class User.
	system += buyer;		// We used operator+=, that was created in class System, and adds user to system's array of users.
	cout << endl;
	cout << "Buyer's list:\n";
	system.showUsersDetails("Buyer");

	// Add seller
	cout << endl;
	Address address2("Israel", "Hertzeliya", "RBH", 11, 68185);
	Seller seller("idan123", "123", address2);
	cout << "The seller that is need to be added is: " << seller.getName(); // We used Operator<< here, in the class User.
	system += seller;		// We used operator+=, that was created in class System, and adds user to system's array of users.
	cout << endl;
	cout << "Seller's list:\n";
	system.showUsersDetails("Seller");
}


// Operator>:
void Menu::ActOperator2(System &system)
{
	Address address1("Israel", "Even-Yehuda", "HayeletHashahar", 12, 40500);
	Buyer buyer("erezlev13", "123", address1);
	Address address3("Israel", "Jerusalem", "ABC", 10, 123456);
	Buyer buyer2("yoram", "123", address3);
	PremiumUser premium("abc", "123", address3);

	buyer.getBuyerCart()->addToCart(Product("a", 130, (Product::eCategory)2));
	buyer2.getBuyerCart()->addToCart(Product("b", 100, (Product::eCategory)2));

	cout << "Check for operator> in Buyer class:\n";
	cout << endl;
	cout << "After first adding to cart operation:\n";
	cout << "The " << buyer.getName() << "'s total price of cart is " << buyer.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << "The " << buyer2.getName() << "'s total price of cart is " << buyer2.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << endl;
	if (buyer > buyer2)
		cout << buyer.getName() << "'s price of cart is bigger." << endl;
	else if (buyer2 > buyer)
		cout << buyer2.getName() << "'s price of cart is bigger." << endl;
	else
		cout << buyer.getName() << "'s price of cart is equal to " << buyer2.getName() << "'s price cart.\n";

	buyer.getBuyerCart()->addToCart(Product("c", 100, (Product::eCategory)2));
	buyer2.getBuyerCart()->addToCart(Product("d", 140, (Product::eCategory)2));

	cout << endl;
	cout << "After second adding to cart operation:\n";
	cout << "The " << buyer.getName() << "'s total price of cart is " << buyer.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << "The " << buyer2.getName() << "'s total price of cart is " << buyer2.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << endl;
	if (buyer > buyer2)
		cout << buyer.getName() << "'s price of cart is bigger." << endl;
	else if (buyer2 > buyer)
		cout << buyer2.getName() << "'s price of cart is bigger." << endl;
	else
		cout << buyer.getName() << "'s price of cart is equal to " << buyer2.getName() << "'s price cart.\n";
	cout << endl;
	cout << endl;
	
	// Operator> with premium user: 
	premium.getBuyerCart()->addToCart(Product("e", 500, (Product::eCategory)2));
	cout << "After adding to cart operation, with premium user:\n";
	cout << "The " << buyer.getName() << "'s total price of cart is " << buyer.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << "The " << premium.getName() << "'s total price of cart is " << premium.getBuyerCart()->sumProductsInCartPrice() << endl;
	cout << endl;
	if (buyer > premium)
		cout << buyer.getName() << "'s price of cart is bigger." << endl;
	else if(premium > buyer)
		cout << premium.getName() << "'s price of cart is bigger." << endl;
	else
		cout << buyer.getName() << "'s price of cart is equal to " << premium.getName() << "'s price cart.\n";
	cout << endl;
}


// Opeartor<<:
void Menu::ActOperator3(System &system)
{

	Address address1("Israel", "Even-Yehuda", "HayeletHashahar", 12, 40500);
	Buyer buyer("erezlev13", "123", address1);

	cout << "Here we have the prints of the operator<<:\n";
	cout << endl;
	// User's operator<<
	cout << "Operarot<< of user(buyer):\n" << buyer; // We used Operator<< here, in the class User.
	
	cout << endl;
	// Product's operator<<
	cout << "\nProduct's print with operator<<:\n";
	cout << Product("a", 130, (Product::eCategory)2) << endl;

	// Address's operator<<
	cout << "Address's print with operator<<:\n";
	cout << address1;
	cout << endl;
}


void Menu::Exit(System &system)
{
	ofstream outFile("systemData.txt", ios::out);
	system.writeToFile(outFile);
	cout << "Exit from menu." << endl;
	outFile.close();
}


// Main's Methods
vector<Product*> Menu::makeOrderedProducts(Buyer &buyer)
{
	int productIndex;
	vector<Product*> newOrderedProducts;

	// we allocate the size of the products array with size of cart +1 in order
	//to put nullptr at the end(thats how we know order's size.
	if (buyer.getBuyerCart() == nullptr || buyer.getBuyerCart()->getSize() == 0)
	{
		cout << "This buyer has no products in cart.\n";
	}
	else
	{
		// = new Product*[buyer.getBuyerCart()->getSize() + 1];

		cout << "Choose the products you want to order, by entering the number on the left: " << endl;
		buyer.getBuyerCart()->showAllProductsInCart();

		cout << "Enter the numbers of the products, for finish ordering enter 0.\n";
		cin >> productIndex;
		while (productIndex != 0)
		// Lets the buyer enter all the products he want to add to the order.
		{
			if (productIndex > buyer.getBuyerCart()->getSize())
			{
				cout << "You have entered unvalid product index.\n";
				cout << "Please enter a number from the list, that is presented to you, or press 0 for finish: ";
			}
			else
			{
				// Enter the product he want to add to the order. productIndex match to the products list.
				//newOrderedProducts[logSize++] = buyer.getBuyerCart()->getProducts()[productIndex - 1];
				newOrderedProducts.push_back(buyer.getBuyerCart()->getProducts()->getElement(productIndex - 1));
				//cout << "You have added " << buyer.getBuyerCart()->getProducts()[productIndex - 1]->getProductName();
				cout << "You have added " << buyer.getBuyerCart()->getProducts()->getElement(productIndex - 1)->getProductName();
				cout << " to your order list.\n";

				// Removes one product that need to be added to buyer's cart.
				buyer.getBuyerCart()->removeProductFromCart(productIndex - 1);
				if (buyer.getBuyerCart()->getSize() == 0)
				{
					cout << "Your cart is empty.\n";
					break;
				}
				cout << "Choose the products you want to order, by entering the number on the left: " << endl;
				buyer.getBuyerCart()->showAllProductsInCart();

			}
					
		cin >> productIndex;
		}
	}
	return newOrderedProducts;
}


void Menu::printMenu()
{
	cout << "(1)" << "  Add buyer" << endl;
	cout << "(2)" << "  Add seller" << endl;
	cout << "(3)" << "  Add product to seller's shop" << endl;
	cout << "(4)" << "  Add feedback" << endl;
	cout << "(5)" << "  Add product to cart" << endl;
	cout << "(6)" << "  Place order" << endl;
	cout << "(7)" << "  Pay for order" << endl;
	cout << "(8)" << "  Show buyer's list" << endl;
	cout << "(9)" << "  Show seller's list" << endl;
	cout << "(10)" << " Show all products details with certain name" << endl;
	cout << "(11)" << " Add Buyer-Seller(Premium)" << endl;
	cout << "(12)" << " Show premium's list" << endl;
	cout << "(13)" << " Show same kind of user type" << endl;
	cout << "(14)" << " Act operator+=" << endl;
	cout << "(15)" << " Act operator>" << endl;
	cout << "(16)" << " Act operator<<" << endl;
	cout << "(17)" << " Exit" << endl;
}


void Menu::cleanBuffer()
{
	int c;
	do {
		c = getchar();
	} while (c != EOF && c != '\n');
}