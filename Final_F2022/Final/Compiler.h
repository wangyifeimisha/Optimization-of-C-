//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMPILER_H
#define COMPILER_H

#include "Theory.h"

class Compiler : public Theory
{
public:
	Compiler();
	Compiler(const Compiler &) = delete;
	Compiler &operator = (const Compiler &) = delete;
	~Compiler();

	virtual void Add(Language *const pNode);
	virtual void Print();

	// ------------------------------------------
	// Data:  (do not add or modify the data)
	// ------------------------------------------
public:
	Language *poFirst;
};

#endif

// --- End of File ---
