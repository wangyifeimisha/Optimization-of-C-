//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef J_H
#define J_H

class Dog
{
public:
	int *pVal;

	Dog(int val);
	Dog(const Dog& d);
	~Dog();

	static int GetVal(Dog d);
};

#endif

// End of File
