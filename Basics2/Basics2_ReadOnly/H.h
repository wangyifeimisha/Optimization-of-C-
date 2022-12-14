//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef H_H
#define H_H

#include "F.h"
#include "G.h"

// ----------------------------------------------------------------------
//
// Problem 3
//
// Related files:  E.h, F.h, G.h, H.h
//
// Rules: 
//     Modify the classes to pass tests
//     The class should be in a diamond inheritance pattern
//     Only one variable in (H: a,b,c,d ) no duplicates or replicas
//
//     1) Do NOT modify class E in any way
//     2) Do NOT modify class H in any way
//     3) Refactor class F to pass tests
//     4) Refactor class G to pass tests
//
// ----------------------------------------------------------------------

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

class H : public F, public G
{
public:
	H();

	void foo();

	int d;
};

#endif

// --- End of File ---
