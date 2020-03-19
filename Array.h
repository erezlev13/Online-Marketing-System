#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
using namespace std;

/*
This template class is been used in class Cart as the array of Product*.
*/


template<class T>
class Array {
private:
	int logicSize;
	T *m_arr;
public:
	Array()
	{
		logicSize = 0;
		m_arr = new T[1];
	}
	Array(const Array &other)
	{
		*this = other;
	}
	~Array()
	{
		delete[] m_arr;
	}


	const Array<T> &operator=(const Array<T> &other)
	{
		if (this != &other)
		{
			logicSize = other.logicSize;
			delete[] m_arr;
			m_arr = new T[logicSize];
			for (int i = 0; i < logicSize; i++)
			{
				m_arr[i] = other.m_arr[i];
			}
		}
		return *this;
	}

	void operator=(const T &element)
	{
		m_arr[logicSize] = element;
	}


	friend ostream &operator<<(ostream &os, const Array &arr)
	{
		for (int i = 0; i < arr.logicSize; i++)
		{
			os << arr.m_arr[i];
		}
		return os;
	}

	int getSize()
	{
		return logicSize;
	}

	void increaseSize()
	{
		logicSize++;
	}

	void addToArray(T elementToAdd)
	{
		m_arr[logicSize] = elementToAdd;
	}

	void decreaseSize()
	{
		logicSize--;
	}

	T getElement(int index)
	{
		return m_arr[index];
	}

	void emptyCell(int index)
	// This methos works on array of pointers.
	{
		m_arr[index] = nullptr;
	}

	
	void arraySwap(int elem1Index, int elem2Index)
	{
		swap(m_arr[elem1Index], m_arr[elem2Index]);
	}


	void modifyArray()
		/*
		This method creates a new array bigger than one with the old array's size(usually).
		It copies the data from the old array to the new array.
		Then, it deletes the old array and returns the new array.
		*/
	{
		T *newArray;					//Creates a new array of pointers.
		newArray = new T[logicSize + 1];	//Allocates it.
		for (int i = 0; i < logicSize; i++)		// Loops that copies the organs to the new array.
		{
			newArray[i] = m_arr[i];
		}
		T* tmp;				// Creates a temporary variable to keep the m_products address.
		tmp = m_arr;			// Keeps the address of previous pointers.
		m_arr = newArray;	// Puts the address of the new Products at the pervious products array. 
		newArray = nullptr;
		delete[] tmp;				// Free the memory of the previous pointer array.
	}
};




#endif // __ARRAY_H