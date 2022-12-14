//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef THEORY_H
#define THEORY_H

// after all... everything works in Theory

#include "Language.h"

class Theory
{
public:
	Theory();
	Theory(const Theory &) = delete;
	Theory &operator = (const Theory &) = delete;
	virtual ~Theory();  

	virtual void Print() = 0;
	virtual void Add(Language *const pTmp) = 0;

	// ------------------------------------------
	// Data:  (do not add or modify the data)
	// ------------------------------------------
public:
	int Count;
};

#endif

// --- End of File ---
