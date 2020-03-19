
#ifndef __FEEDBACK_H

#define __FEEDBACK_H

#include "date.h"
#include "validation.h"
#include <string>
using namespace std;


class Feedback
{
public:
	// Constructors:
	Feedback(const string& bodyFeedback, const Date &date, string& buyerUserName,int productSerialNumber);
	Feedback(Feedback &&other);								 // Move c'tor
	~Feedback();											 // Destructor

	// Gets
	const string getBody()			const;
	Date getDate()					const;
	string getBuyerUserName()		const;

	// Sets
	void setBody(const string& body);
	bool setFeedbackDate(const Date &date);
	void setBuyerUserName(string& buyerUserName);

private:
	string m_body;
	Date m_feedbackDate;
	string m_buyerUserName;
	int m_producrSerialNumber;
};

#endif // __FEEDBACK_H

