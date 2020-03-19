#pragma warning(disable:4996)
#include "feedback.h"
#include "date.h"
#include <string.h>
#include <iostream>
using namespace std;




// Constructors:
// Constructor
Feedback::Feedback(const string& bodyFeedback, const Date &date, string& buyerUserName, int productSerialNumber)
	:m_feedbackDate(date)
{
	m_body = bodyFeedback;
	m_buyerUserName = buyerUserName;
	m_producrSerialNumber = productSerialNumber;
}



// Move Constructor
Feedback::Feedback(Feedback &&other) :m_feedbackDate(other.m_feedbackDate)
{
	m_body = move(other.m_body);
	m_producrSerialNumber = other.m_producrSerialNumber;
	m_buyerUserName = move(other.m_buyerUserName);
}




//Destructor
Feedback::~Feedback()
{
}


// Gets
const string Feedback::getBody()		const
{
	return m_body;
}


Date Feedback::getDate()			const
{
	return m_feedbackDate;
}


string Feedback::getBuyerUserName()	const
{
	return m_buyerUserName;
}


// Sets
void Feedback::setBody(const string& body)
{
	m_body = body;
}


bool Feedback::setFeedbackDate(const Date &date)
{
	if (m_feedbackDate.setDate(date.getDay(), date.getMonth(), date.getYear()) == true)
		return true;
	else
		return false;
}


void Feedback::setBuyerUserName(string& buyerUserName)
{
	m_buyerUserName = buyerUserName;
}