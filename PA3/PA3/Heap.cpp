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

void Heap::SetFreeHead(Free* p)
{
    assert(p);
    this->pFreeHead = p;
}

void Heap::SetNextFit(Free* p)
{
    assert(p);
    this->pNextFit = p;
}

void Heap::AddFreeBlock(uint32_t BlockSize)
{
    this->currFreeMem += BlockSize;
    this->currNumFreeBlocks++;
}

void Heap::RemoveFreeBlock(uint32_t BlockSize)
{
    this->currFreeMem -= BlockSize;
    this->currNumFreeBlocks--;
}


void Heap::SetUsedHead(Used* p)
{
    assert(p);
    this->pUsedHead = p;
}

void Heap::AddUsedBlock(uint32_t BlockSize)
{
    this->currUsedMem += BlockSize;
    this->currNumUsedBlocks++;
}
void Heap::RemoveUsedBlock(uint32_t BlockSize)
{
    this->currUsedMem -= BlockSize;
    this->currNumUsedBlocks--;
}
// --- End of File ---
