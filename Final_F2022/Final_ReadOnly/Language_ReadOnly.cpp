//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "Language.h"

Language::Language(const char *const name)
{
	unsigned int size = strlen(name) + 1;
	this->poType = new char[size];
	strcpy_s(this->poType, size, name);
	this->pNext = nullptr;
}

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

// --- End of File ---
