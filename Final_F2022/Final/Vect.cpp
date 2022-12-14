//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect.h"

// -------------------------------------------------------
// Must use CDM::Sqrt() for sqrt in Vect or Proxy class
//--------------------------------------------------------

LengthProxy Vect::Len()
{
	//float len;
	//len = CDM::Sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	//return len;

	return LengthProxy(this->x, this->y, this->z);
}

Vect::Vect(float a, float b, float c)
	: x(a),
	y(b),
	z(c)
{

}

// ---  End of File ---

