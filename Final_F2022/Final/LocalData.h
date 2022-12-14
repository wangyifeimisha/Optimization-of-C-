//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef LOCAL_DATA_H
#define LOCAL_DATA_H

#include <vector>

struct LocalData
{
	LocalData() = default;
	LocalData(const LocalData &) = default;
	LocalData& operator = (const LocalData &) = default;
   ~LocalData() = default;

	// Add methods here:
   float getAverage();
	// ------------------------------------------
	// Data:  (do not add or modify the data)
	// ------------------------------------------
	std::vector<int> vect;

};

#endif

// ---  End of File ---
