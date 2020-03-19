#ifndef __PREMIUMUSER_H
#define __PREMIUMUSER_H


#include "buyer.h"
#include "seller.h"
#include <iostream>
#include <string>

class PremiumUser :public Seller, public Buyer {
public:
	// Constructors:
	PremiumUser(const string userName, const string password, const Address& address);	// Constructor
	virtual ~PremiumUser();																// Destructor

	// Gets
	virtual string getName()	const override;
};






#endif // __PREMIUMUSER_H