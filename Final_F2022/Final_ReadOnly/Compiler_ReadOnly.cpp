//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "Compiler.h"

Compiler::Compiler()
{
	this->poFirst = nullptr;
}

void Compiler::Add(Language *const pNode)
{
	this->Count++;

	if (poFirst != nullptr)
	{
		pNode->pNext = this->poFirst;
	}
	this->poFirst = pNode;
}

void Compiler::Print()
{
	Trace::out("\tCount: %d\n", this->Count);
	Language *pTmp = this->poFirst;
	while (pTmp != nullptr)
	{
		Trace::out("\t\t%s\n", pTmp->poType);
		pTmp = pTmp->pNext;
	}
}

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

// --- End of File ---
