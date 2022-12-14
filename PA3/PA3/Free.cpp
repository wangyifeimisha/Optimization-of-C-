//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Used.h"
#include "Free.h"
#include "Type.h"

// Add magic here
Free::Free(uint32_t blockSize)
	:mAllocSize((uint16_t)blockSize),
	mType(Type::FREE_Type),
	bAboveFree(false),
	pNext(nullptr),
	pPrev(nullptr)
{
}
// ---  End of File ---
