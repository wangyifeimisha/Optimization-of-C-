//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PROXY_H
#define PROXY_H

// -------------------------------------------------------
// Must use CDM::Sqrt() for sqrt in Vect or Proxy class
//--------------------------------------------------------

// Add proxy here
struct LengthProxy
{
	const float f1;
	const float f2;
	const float f3;

	LengthProxy();
	~LengthProxy() = default;

	LengthProxy(float _f1, float _f2, float _f3);

	bool operator == (const LengthProxy& rhs) const;
	bool operator != (const LengthProxy& rhs) const;
	bool operator > (const LengthProxy& rhs) const;
	bool operator >= (const LengthProxy& rhs) const;
	bool operator < (const LengthProxy& rhs) const;
	bool operator <= (const LengthProxy& rhs) const;

	operator float() const;
};
#endif

// ---  End of File ---


