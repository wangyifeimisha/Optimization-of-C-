//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NYBLE_H
#define NYBLE_H

//----------------------------------------------------------------------------
// Feel free to add extra methods in the class
// You need to explicitly define and implement the Big four operators
// Do not add extra data in class
// Do not add code here (that goes in *.cpp)
//----------------------------------------------------------------------------

class Nyble
{
public:
	// insert your code here
	Nyble();
	Nyble(const Nyble& n);
	Nyble& operator= (const Nyble& n);
	~Nyble();

	Nyble(unsigned int _data);

	Nyble operator+(const Nyble& rhs) const;
	Nyble operator+(int _i) const;
	Nyble& operator+=(const Nyble& rhs);
	
	friend Nyble operator+(int _x, const Nyble& n);
	
	Nyble& operator++();					//prefix increment
	Nyble operator++(int);			//postfix increment

	Nyble operator+()const;		// Unary plus
	Nyble operator~()const;		// Bitwise complement
	Nyble operator<<(const int _i)const;		// Left shift
	
	operator unsigned int() const;

	unsigned char getData();

private:
        // Do not change this data
	unsigned char data;

};

Nyble operator+ (int _x, const Nyble& n);
#endif

//---  End of File ---
