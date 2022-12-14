//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VECT_H
#define VECT_H

#include "CDM.h"
#include "Proxy.h"

// --------------------------------------------------------------------------------------------------------------------------------------
//  Please REFACTOR Vect class, feel free to add/delete/modify any method.
//          Add a Proxy structures/classes to accomplish the goal:
//                Len() method should _NOT_ call CDM::Sqrt() for comparison operators
//                                  ==, !=, >, >=, <, <=     (no sqrt() calls allowed)
//                float val = A.Len();    ( is allowed to call CDM::Sqrt() )
//          You will need to change the existing code and refactor.
// ---------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------
// Must use CDM::Sqrt() for sqrt in Vect or Proxy class
//--------------------------------------------------------
class Vect
{
public:
	Vect() = default;
	Vect(const Vect &) = default;
	Vect &operator = (const Vect &) = default;
	~Vect() = default;

	Vect(float a, float b, float c);

	// -------------------------------------------------------
	// Must use CDM::Sqrt() for sqrt in Vect or Proxy class
	//--------------------------------------------------------

	// Add or modify methods here:	
	LengthProxy Len();

// ------------------------------------------
// Data:  (do not add or modify the data)
// ------------------------------------------
private:
	float x;
	float y;
	float z;

};

#endif

// ---  End of File ---

