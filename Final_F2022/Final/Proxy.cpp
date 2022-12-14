//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CDM.h"
#include "Proxy.h"

// -------------------------------------------------------
// Must use CDM::Sqrt() for sqrt in Vect or Proxy class
//--------------------------------------------------------

// Add Proxy here

LengthProxy::LengthProxy()
	:f1(0.0f), f2(0.0f), f3(0.0f)
{
	// do nothing
}

LengthProxy::LengthProxy(float _f1, float _f2, float _f3)
	:f1(_f1), f2(_f2), f3(_f3)
{
	// do nothing
}

bool LengthProxy::operator == (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 == rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

bool LengthProxy::operator != (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 != rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

bool LengthProxy::operator > (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 > rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

bool LengthProxy::operator >= (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 >= rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

bool LengthProxy::operator < (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 < rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

bool LengthProxy::operator <= (const LengthProxy& rhs) const
{
	return this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3 <= rhs.f1 * rhs.f1 + rhs.f2 * rhs.f2 + rhs.f3 * rhs.f3;
}

LengthProxy::operator float() const 
{
	float len;
	len = CDM::Sqrt(this->f1 * this->f1 + this->f2 * this->f2 + this->f3 * this->f3);
	return len;
}

// ---  End of File ---

