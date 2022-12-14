//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "BucketMan.h"

// ------------------------------------------------
// Do All work in the destructor Only
// ------------------------------------------------
BucketMan::~BucketMan()
{
	Bucket* pTmp = this->poHead;
	Bucket* pDeleteMe = pTmp;

	while (pTmp)
	{
		pDeleteMe = pTmp;
		pTmp = pTmp->pNext;
		delete pDeleteMe;
	}
}

// --- End of File ---

