#ifndef __DATE_H

#define __DATE_H

#include <string.h>
using namespace std;


class Date
{
public:
	// Constructors:
	Date(int day, int month, int year);	// Constructor
	~Date();							// Destructor

	// Gets:
	int getDay()	const;
	int getMonth()	const;
	int getYear()	const;

	// Sets:
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	// Methods
	bool setDate(int day, int month, int year);

private:
	int m_day;
	int m_month;
	int m_year;
};

#endif // __DATE_H
