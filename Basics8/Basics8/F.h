//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef F_H
#define F_H

// MODIFY this file

// There should be two classes defined in this header
//     Generalized template class
//     Full class specification class 
//
// Generalized: Cut & Paste from E.h for the general class template
//     Then add a second full specialization class
//
// Write a full class specialization for float
//     in this class when you push() a float it pushes the data twice
//     in this class when you pop() it pops a singe element off the stack
//     top() and empty() behave the same.

#include <vector>

template <typename T>
class StackF
{
public:
	// Write the following functions

	// push element
	void push(T const & data)
	{
		// shut up compiler - replace
		elems.push_back(data);
	}

	// pop element
	void pop()
	{
		elems.pop_back();
	}

	// return top element
	T top() const
	{
		return elems[elems.size() - 1];
	}

	// return whether the stack is empty
	bool empty() const
	{
		if (elems.size() == 0)
		{
			return true;
		}
		return false;
	}

private:
	std::vector<T> elems;     // elements
};


template <>
class StackF <float>
{
public:
	// Write the following functions

		// push element
	void push(float const& data)
	{
		// shut up compiler - replace
		elems.push_back(data);
		elems.push_back(data);
	}

	// pop element
	void pop()
	{
		elems.pop_back();
	}

	// return top element
	float top() const
	{
		return elems[elems.size() - 1];
	}

	// return whether the stack is empty
	bool empty() const
	{
		if (elems.size() == 0)
		{
			return true;
		}
		return false;
	}

private:
	std::vector<float> elems;     // elements
};

#endif

// ---  End of File ---------------
