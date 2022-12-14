//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "BucketMan.h"
#include "Bucket.h"

// ------------------------------------------------
// Do All work in the destructor Only
// ------------------------------------------------
Bucket::~Bucket()
{
	// only 1 item in bucketman
	if (!this->pPrev && !this->pNext)
	{
		this->pMan->poHead = nullptr;
		this->pMan = nullptr;
		
		Item* pTmp = this->poHead;
		Item* pDeleteMe = pTmp;

		while (pTmp)
		{
			pDeleteMe = pTmp;
			pTmp = pTmp->pNext;
			delete pDeleteMe;
		}
	}
	// first element 
	else if (!this->pPrev)
	{
		this->pMan->poHead = this->pNext;
		this->pMan = nullptr;
		this->pNext->pPrev = nullptr;
		this->pNext = nullptr;
		
		Item* pTmp = this->poHead;
		Item* pDeleteMe = pTmp;

		while (pTmp)
		{
			pDeleteMe = pTmp;
			pTmp = pTmp->pNext;
			delete pDeleteMe;
		}
	}
	// last element
	else if (!this->pNext)
	{
		this->pMan = nullptr;
		this->pPrev->pNext = nullptr;
		this->pPrev = nullptr;
		
		Item* pTmp = this->poHead;
		Item* pDeleteMe = pTmp;

		while (pTmp)
		{
			pDeleteMe = pTmp;
			pTmp = pTmp->pNext;
			delete pDeleteMe;
		}
	}

	else
	{
		this->pMan = nullptr;
		this->pNext->pPrev = this->pPrev;
		this->pPrev->pNext = this->pNext;
		this->pNext = nullptr;
		this->pPrev = nullptr;
		
		Item* pTmp = this->poHead;
		Item* pDeleteMe = pTmp;

		while (pTmp)
		{
			pDeleteMe = pTmp;
			pTmp = pTmp->pNext;
			delete pDeleteMe;
		}
	}
	
}

// --- End of File ---

