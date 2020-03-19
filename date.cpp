#pragma warning(disable:4996)
#include "date.h"
#include "validation.h"
#include <string.h>
using namespace std;



// Constructors:
// Constructor
Date::Date(int day, int month, int year)
{
	setDate(day, month, year);
}
//Destructor
Date::~Date()
{
}


// Gets:
int Date::getDay()const
{
	return m_day;
}
int Date::getMonth()const
{
	return m_month;
}
int Date::getYear()const
{
	return m_year;
}


// Sets:
void Date::setDay(int day)
{
	m_day = day;
}

void Date::setMonth(int month)
{
	m_month = month;
}

void Date::setYear(int year)
{
	m_year = year;
}

// Methods
bool Date::setDate(int day, int month, int year)
// Method that checks if the date is valid.
{
	if (Validation::isValidDate(day, month, year) == true)
	{
		setDay(day);
		setMonth(month);
		setYear(year);
		return true;
	}
	return false;
}