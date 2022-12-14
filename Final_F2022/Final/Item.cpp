//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Bucket.h"
#include "Item.h"

// ------------------------------------------------
// Do All work in the destructor Only
// ------------------------------------------------
Item::~Item()
{
	// only 1 item in bucket
	if (!this->pPrev && !this->pNext)
	{
		this->pBucket->poHead = nullptr;
		this->pBucket = nullptr;
		delete this->poData;
	}
	// first element 
	else if (!this->pPrev)
	{
		this->pBucket->poHead = this->pNext;
		this->pBucket = nullptr;
		this->pNext->pPrev = nullptr;
		this->pNext = nullptr;
		delete this->poData;
	}
	// last element
	else if (!this->pNext)
	{
		this->pBucket = nullptr;
		this->pPrev->pNext = nullptr;
		this->pPrev = nullptr;
		delete this->poData;
	}

	else
	{
		this->pBucket = nullptr;
		this->pNext->pPrev = this->pPrev;
		this->pPrev->pNext = this->pNext;
		this->pNext = nullptr;
		this->pPrev = nullptr;
		delete this->poData;
	}
}

// --- End of File ---

