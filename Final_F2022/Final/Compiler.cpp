//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Compiler.h"

Compiler::~Compiler()
{
	Language* pTmp = this->poFirst;
	Language* pDeleteMe = pTmp;

	while (pTmp)
	{
		pDeleteMe = pTmp;
		pTmp = pTmp->pNext;
		delete pDeleteMe;
	}
}



// --- End of File ---
