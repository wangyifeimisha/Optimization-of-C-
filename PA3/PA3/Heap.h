//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef HEAP_H
#define HEAP_H

#include "Used.h"
#include "Free.h"


class Heap
{

public:
	// Big four
	Heap();
	Heap(const Heap&) = delete;
	Heap& operator =(const Heap&) = delete;
	~Heap() = default;

	// helper function
	void SetFreeHead(Free* p);
	void SetNextFit(Free* p);
	void AddFreeBlock(uint32_t BlockSize);
	void RemoveFreeBlock(uint32_t BlockSize);
	void SetUsedHead(Used* p);
	void AddUsedBlock(uint32_t BlockSize);
	void RemoveUsedBlock(uint32_t BlockSize);

public:
	// allocation links
	Used	    *pUsedHead;
	Free	    *pFreeHead;

	// Next fit allocation strategy
	Free        *pNextFit;

	uint32_t    currNumUsedBlocks;   // number of current used allocations
	uint32_t    currUsedMem;         // current size of the total used memory

	uint32_t    currNumFreeBlocks;   // number of current free blocks
	uint32_t    currFreeMem;         // current size of the total free memory

	uint32_t    pad;
};

#endif 

// --- End of File ---
