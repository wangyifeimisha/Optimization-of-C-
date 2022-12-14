//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>

#include "D.h"
#include "Vect.h"

Vect V[] =
{
	{3,5,6},
	{6,5,3},
	{3,4,7},
	{7,2,5},
	{1,3,5},
	{3,2,5},
	{2,3,4},
	{3,5,5},
	{7,3,2},
	{4,3,2},
	{1,7,1}
};

Vect JunkDataD{ 0xa,0xb,0x3 };


bool cmpVect(Vect v1, Vect v2)
{
	if (v1.a != v2.a)
	{
		return (v1.a < v2.a);
	}
	else if (v1.b != v2.b)
	{
		return (v1.b < v2.b);
	}
	else
	{
		return (v1.c < v2.c);
	}
}


void Problem_D(	std::vector< Vect > &UnitTest_V_orig,
				std::vector< Vect > &UnitTest_V_sort)
{	
	// ----------------------------------------------------
	// a) Load the V[] data into a vector
	//    Name the vector: v
	// ----------------------------------------------------

		// ADD CODE HERE:
		std::vector<Vect> v{ std::begin(V), std::end(V) };  // <-- REPLACE this LINE... shuts up warnings, its 100% wrong

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_V_orig.assign(v.begin(), v.end());

	// ----------------------------------------------------
	// b) Sort the new STL vector with strict weak ordering
	//    Don't know what strict weak ordering is... Look it up
	// ----------------------------------------------------

		// ADD CODE HERE:
		std::sort(v.begin(), v.end(), cmpVect);

		// ---------------------------------------------------------------------
		// Copies STL to gobal for unit test (Do NOT Remove or modify next line)
		// ---------------------------------------------------------------------
		UnitTest_V_sort.assign(v.begin(), v.end());
}

// ---  End of File ---
