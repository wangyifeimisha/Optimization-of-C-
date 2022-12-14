//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Nyble.h"

Nyble::Nyble()
	:data(0)
{
	//this->data = 0;
}

Nyble::Nyble(unsigned int _data)
{
	unsigned int maskData = _data & 0x0F;
	unsigned char charData = (unsigned char)maskData;
	this->data = charData;
}

Nyble::Nyble(const Nyble& n)
	: data(n.data)
{
	//this->data = n.data;
}

Nyble& Nyble::operator= (const Nyble& n)
{
	this->data = n.data;
	return *this;
}

Nyble::~Nyble()
{
	// do nothing
}

Nyble Nyble::operator+(const Nyble& rhs)const
{
	Nyble temp;
	temp.data = (unsigned char)(0x0F & (int)(this->data +rhs.data));
	return temp;
}



Nyble Nyble::operator+ (int _i) const
{
	Nyble temp;
	temp.data = (unsigned char)(0x0F & (int)(this->data + _i));
	return temp;
}

Nyble& Nyble::operator+= (const Nyble& rhs)
{
	this->data = (unsigned char)((this->data + rhs.data) & 0x0F);
	return *this;
}

Nyble operator+(int _x, const Nyble& n)
{
	unsigned int addResult = (unsigned int)(_x + n.data);
	Nyble temp(addResult);
	return temp;
}

Nyble& Nyble::operator++ ()
{
	this->data++;
	if (this->data > 0x0F) this->data = (unsigned char)(this->data & 0x0F);
	return *this;
}


Nyble Nyble::operator++ (int)
{		
	unsigned char i = this->data;
	this->data++;
	if (this->data > 0x0F) this->data = (unsigned char)(this->data & 0x0F);
	Nyble temp;
	temp.data = i;
	return temp;
}

Nyble Nyble::operator+() const
{
	int i = (int)this->data + 3;
	Nyble temp;
	temp.data = (unsigned char)(i & 0x0F);
	return temp;
}

Nyble Nyble::operator~() const
{
	int sub = 0x0F -(int)this->data;
	Nyble temp;
	temp.data = (unsigned char)sub;
	return temp;
}

Nyble Nyble::operator<< (const int _i)const
{
	int mark = _i & 0x03;
	if ( mark == 0) return Nyble(*this);
	
	unsigned int init = (unsigned int)this->data;
	unsigned int rotationalBits = 0;

	switch (mark) {
	case 1:
		rotationalBits = 8;
		break;
	case 2:
		rotationalBits = 12;
		break;
	case 3:
		rotationalBits = 14;
		break;
	default:
		// do nothing
		//Q4: why is this break needed? Cause syntax error
		break;
	}

	unsigned int savedBits = init & rotationalBits;
	switch (mark) {
	case 1:
		savedBits = savedBits >> 3;
		break;
	case 2:
		savedBits = savedBits >> 2;
		break;
	case 3:
		savedBits = savedBits >> 1;
		break;
	default:
		// do nothing
		break;
	}

	init = init << _i;
	init &= 0x0F;
	init |= savedBits;
	Nyble temp = Nyble(init);
	return temp;
}
 
Nyble::operator unsigned int() const
{
	unsigned int result = (unsigned int)this->data - 3;
	return result;
}

unsigned char Nyble::getData()
{
	return this->data;
}


//---  End of File ---
