//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Heap.h"
#include "Mem.h"

Heap::Heap()
:	pUsedHead(nullptr),
	pFreeHead(nullptr),
	pNextFit(nullptr),
    currNumUsedBlocks(0),
    currUsedMem(0),
    currNumFreeBlocks(0),
    currFreeMem(0)
{
}

// Added helper function
void Heap::SetFreeHead(Free* const p)
{
    assert(p);
    this->pFreeHead = p;
}

void Heap::SetNextFit(Free* const p)
{
    assert(p);
    this->pNextFit = p;
}

void Heap::AddFreeBlock(const uint32_t BlockSize)
{
    this->currFreeMem += BlockSize;
    this->currNumFreeBlocks++;
}



// --- End of File ---
