//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// Add additional includes if you want

// Some includes that might be useful
// Allowed to use STL algorithm
#include <algorithm>
#include <functional>   
#include <numeric> 

#include "LocalData.h"

// Add methods here
float LocalData::getAverage()
{
	float result = (float)std::accumulate(this->vect.begin(), this->vect.end(), 0.0);
	result /= (float)this->vect.size();
	return result;
}


// ---  End of File ---

