//-----------------------------------------------------------------------------
// Copyright 2nullptr22, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Mem.h"
#include "Heap.h"
#include "Type.h"

// To help with coalescing... not required
struct SecretPtr
{
	Free *pFree;
};

// ----------------------------------------------------
//  Initialized the Memory block:
//  Update the Heap
//  Create a free block
//  Heap structure links to free hdr
//-----------------------------------------------------
void Mem::initialize()
{
	Heap* pHeap = this->poHeap;
	assert(pHeap);

	// Get the location of Free Header
	Free* pFreeStart = (Free*)(pHeap + 1);

	// Get the size of Block
	uint32_t BlockStart = (uint32_t)(pFreeStart + 1);
	uint32_t BlockEnd = ((uint32_t)pHeap + TotalSize);
	uint32_t mAllocSize = BlockEnd - BlockStart;

	// Create Free at Address
	Free* pFree = new(pFreeStart) Free(mAllocSize);

	// Update Heap Information
	pHeap->SetFreeHead(pFree);
	pHeap->SetNextFit(pFree);
	pHeap->AddFreeBlock(mAllocSize);
}

// ----------------------------------------------------
//  Do your Magic here:
//  Find a free block that fits
//  Change it to used (may require subdivision)
//  Correct the heap Links (used,free) headers 
//  Update stats
//  Return pointer to block
//-----------------------------------------------------
void *Mem::malloc( const uint32_t _size )
{
	Heap* pHeap = this->poHeap;

	// Find Free block
	Free* availFree = this->privFindFreeBlock(_size);

	Free* availpNext = availFree->pNext;
	Free* availpPrev = availFree->pPrev;
	uint32_t availFreeSize = (uint32_t)availFree->mAllocSize;

	if (availpNext) availpNext->pPrev = availpPrev;
	if (availpPrev) availpPrev->pNext = availpNext;

	// Create Used block
	Used* startUsed = (Used*)availFree;
	Used* pUsed = new (startUsed)Used(_size);

	// Add Used to Front
	this->privAddUsedToFront(pUsed);

	pUsed->bAboveFree = false;

	uint32_t restSize = availFreeSize - (uint32_t)pUsed->mAllocSize;

	// Perfect fit
	if (restSize == 0)
	{
		pHeap->currNumUsedBlocks++;
		pHeap->currUsedMem += _size;
		pHeap->currNumFreeBlocks--;
		pHeap->currFreeMem -= _size;

		this->privAdjustFreeAfterRemoveAllFree((Free*)availFree);
		
		pHeap->pNextFit = pHeap->pFreeHead;
	}
	else if (restSize < sizeof(Free))
	{
		// ignore
	}
	else
	{
		pHeap->currNumUsedBlocks++;
		pHeap->currUsedMem += (uint32_t)_size;
		pHeap->currFreeMem -= _size + sizeof(Free);

		// Subdivide Free block
		Free* startFree = (Free*)((uint32_t)pUsed + _size + sizeof(Used));
		Free* pFree = new (startFree)Free(restSize);

		pFree->mAllocSize = (uint16_t)restSize - sizeof(Free);
		pFree->pPrev = availpPrev;
		pFree->pNext = availpNext;

		this->privAdjustFreeAfterSubdivide(pFree);
		pHeap->pNextFit = pFree;
		// secrete ptr
		Free** secretPtr = (Free**)((uint32_t)pFree + pFree->mAllocSize + sizeof(Free) - sizeof(Free*));
		*secretPtr = pFree;
	}

	
	if (pHeap->currNumFreeBlocks == 0)
	{
		pHeap->pFreeHead = nullptr;
		pHeap->pNextFit = nullptr;
	}


	uint32_t nextBlockAddr = (uint32_t)pUsed + sizeof(Used) + pUsed->mAllocSize;
	Type belowBlockType = ((Used*)nextBlockAddr)->mType;
	if (belowBlockType == Type::USED_Type)
	{
		Used* nextBlockUsed = (Used*)nextBlockAddr;
		nextBlockUsed->bAboveFree = false;
	}
		
	return (pUsed + 1);
}


// ----------------------------------------------------
//  Do your Magic here:
//  Return the free block to the system
//  May require Coalescing
//  Correct the heap Links (used,free) headers 
//  Update stats
//-----------------------------------------------------
void Mem::free( void * const data )
{
	
	Heap* pHeap = this->poHeap;

	// Find Used block then remove
	Used* pUsed = this->privFindUsedBlock(data);

	bool bAboveFree = (bool)pUsed->bAboveFree;

	this->privAdjustUsedAfterRemove(pUsed);

	
	if (pHeap->currNumUsedBlocks == 0)
	{
		pHeap->pUsedHead = nullptr;
	}

	// Create Free block
	Free* startFree = (Free*)pUsed;
	Free* pFree = new (startFree)Free(pUsed->mAllocSize);
	
	pHeap->currNumUsedBlocks--;
	pHeap->currUsedMem -= pUsed->mAllocSize;
	pHeap->currNumFreeBlocks++;
	pHeap->currFreeMem += pFree->mAllocSize;
	
	pFree->pNext = nullptr;
	pFree->pPrev = nullptr;
	
	if (pHeap->pFreeHead == nullptr)
	{
		pHeap->pFreeHead = pFree;
	}

	// secrete ptr
	Free** secretPtr = (Free**)((uint32_t)pFree + pFree->mAllocSize + sizeof(Free) - sizeof(Free*));
	*secretPtr = pFree;

	

	// If the Free block is at the bottom... no need to consider block under it to do coalescing
	if (((uint32_t)pFree + sizeof(Free) + pFree->mAllocSize) == (uint32_t)pHeap + TotalSize)
	{
		if (bAboveFree)
		{
			// above Free ... secret pointer
			Free** above = (Free**)((uint32_t)pFree - sizeof(Free*));
			Free* aboveFree = *above;

			

			pFree = this->privCoalescingFree(aboveFree, pFree);
			
			*secretPtr = aboveFree;
		}
		else
		{
			// case1: above Used
			if (pHeap->pFreeHead != pFree) this->privAddFreeAtTheBottom(pFree);
			// case2: nothing above
			else pHeap->pNextFit = pHeap->pFreeHead;
		}
		
	}

	// The Free block is not at the bottom... in this case need to consider coalescing above and below
	else
	{
		uint32_t nextBlockAddr = (uint32_t)pFree + sizeof(Free) + pFree->mAllocSize;

		Type belowBlockType = ((Free*)nextBlockAddr)->mType;
		if (belowBlockType == Type::FREE_Type)
		{
			// Case1: below is Free
			Free* belowFree = (Free*)((uint32_t)pFree + sizeof(Free) + pFree->mAllocSize);

			pFree = this->privCoalescingFree(pFree, belowFree);
			// Reset pFreeHead after coalescing Free
			if (pHeap->pFreeHead == belowFree)
			{
				pHeap->pFreeHead = pFree;
			}

			//scrPtr
			secretPtr = (Free**)((uint32_t)pFree + pFree->mAllocSize + sizeof(Free) - sizeof(Free*));
			*secretPtr = pFree;


			if (bAboveFree)
			{
				// above free
				Free** above = (Free**)((uint32_t)pFree - sizeof(Free*));
				Free* aboveFree = *above;

				

				pFree = this->privCoalescingFreeAbove(aboveFree, pFree);

				*secretPtr = aboveFree;
				
			}
			pHeap->pNextFit = this->privSetPNextFit();
		}


		else
		{
			// Case2: below is Used
			// update belowUsed->aboveFree
			Used* belowUsed = (Used*)((uint32_t)pFree + sizeof(Free) + pFree->mAllocSize);
			belowUsed->bAboveFree = true;

			if (bAboveFree)
			{
				// above free
				Free** above = (Free**)((uint32_t)pFree - sizeof(Free*));
				Free* aboveFree = *above;
				this->privAddFreeByAddress(pFree);

				pFree = this->privCoalescingFreeAbove(aboveFree, pFree);

				*secretPtr = aboveFree;

			}
			else
			{
				// above used or above nothing
				this->privAddFreeByAddress(pFree);
				this->privCheckOnlyOneFree();
				pHeap->pNextFit = this->privSetPNextFit();
			}
		}
	}
}

 
 
// Helper functions
Free* Mem::privFindFreeBlock(const uint32_t _size) const
{
	Free* pFreeTmp = this->poHeap->pNextFit;
	Free* pFreeFound = nullptr;
	while (pFreeTmp)
	{
		if (pFreeTmp->mAllocSize >= _size)
		{
			pFreeFound = pFreeTmp;
			break;
		}

		pFreeTmp = pFreeTmp->pNext;
	}

	if (pFreeFound == nullptr)
	{
		pFreeTmp = this->poHeap->pFreeHead;
		while (pFreeTmp)
		{
			if (pFreeTmp->mAllocSize >= _size)
			{
				pFreeFound = pFreeTmp;
				break;
			}

			pFreeTmp = pFreeTmp->pNext;
		}
	}

	return pFreeFound;
}

void Mem::privAddUsedToFront(Used* const pUsed)
{
	Heap* pHeap = this->poHeap;
	pUsed->pPrev = nullptr;
	pUsed->pNext = pHeap->pUsedHead;
	if (pHeap->pUsedHead != nullptr)
	{
		pHeap->pUsedHead->pPrev = pUsed;
	}
	pHeap->pUsedHead = pUsed;
}

void Mem::privAddFreeAtTheBottom(Free* const pFree)
{
	Heap* pHeap = this->poHeap;
	Free* freeHead = pHeap->pFreeHead;
	while (freeHead)
	{
		if (freeHead->pNext == nullptr)
		{
			break;
		}
		freeHead = freeHead->pNext;
	}
	pFree->pPrev = freeHead;
	freeHead->pNext = pFree;
}

void Mem::privAddFreeByAddress(Free* const pFree)
{
	Heap* pHeap = this->poHeap;
	Free* freeHead = pHeap->pFreeHead;
	if (freeHead > pFree)
	{
		pFree->pNext = pHeap->pFreeHead;
		pHeap->pFreeHead->pPrev = pFree;
		pHeap->pFreeHead = pFree;
	}
	else
	{
		// Find the location
		while (true)
		{
			if (freeHead->pNext > pFree || freeHead->pNext == nullptr)
			{
				break;
			}
			freeHead = freeHead->pNext;
		}

		// Adjust pointers
		if (freeHead->pNext == nullptr)
		{
			freeHead->pNext = pFree;
			pFree->pPrev = freeHead;
			pFree->pNext = nullptr;
		}
		else
		{
			pFree->pPrev = freeHead;
			pFree->pNext = freeHead->pNext;
			freeHead->pNext->pPrev = pFree;
			freeHead->pNext = pFree;
		}
	}
}


Used* Mem::privFindUsedBlock(const void* pRawUsed) const
{
	Used* usedTmp = this->poHeap->pUsedHead;
	
	while (usedTmp)
	{
		if ((void*)(usedTmp + 1) == pRawUsed)return usedTmp;
		usedTmp = usedTmp->pNext;
	}
	return usedTmp;
}



Free* Mem::privCoalescingFree(Free* const pFree1, Free* const pFree2)
{
	Heap* pHeap = this->poHeap;

	pFree1->pNext = pFree2->pNext;
	pFree1->pPrev = pFree2->pPrev;

	if (pFree2->pNext != nullptr)
	{
		pFree2->pNext->pPrev = pFree1;
	}
	if (pFree2->pPrev != nullptr)
	{
		pFree2->pPrev->pNext = pFree1;
	}

	pFree1->mAllocSize = pFree1->mAllocSize + sizeof(Free) + pFree2->mAllocSize;

	pHeap->currFreeMem += sizeof(Free);
	pHeap->currNumFreeBlocks--;

	return pFree1;
}


Free* Mem::privCoalescingFreeAbove(Free* const pFree1, Free* const pFree2)
{
	Heap* pHeap = this->poHeap;

	pFree1->pNext = pFree2->pNext;

	if (pFree2->pNext != nullptr)
	{
		pFree2->pNext->pPrev = pFree1;
	}

	pFree1->mAllocSize = pFree1->mAllocSize + sizeof(Free) + pFree2->mAllocSize;

	pHeap->currFreeMem += sizeof(Free);
	pHeap->currNumFreeBlocks--;

	return pFree1;
}

void Mem::privAdjustFreeAfterRemoveAllFree(const Free* const pFree)
{
	Heap* pHeap = this->poHeap;
	if (pFree->pNext == nullptr && pFree->pPrev == nullptr)
	{
		pHeap->pFreeHead = nullptr;
	}
}

void Mem::privAdjustFreeAfterSubdivide(Free* const pFree)
{
	Heap* pHeap = this->poHeap;
	if (pFree->pPrev == nullptr && pFree->pNext == nullptr)
	{
		pHeap->pFreeHead = pFree;
	}
	else if (pFree->pPrev == nullptr)
	{
		pFree->pNext->pPrev = pFree;
		pHeap->pFreeHead = pFree;
	}
	else if (pFree->pNext == nullptr)
	{
		pFree->pPrev->pNext = pFree;
	}
	else
	{
		pFree->pPrev->pNext = pFree;
		pFree->pNext->pPrev = pFree;
	}
}


void Mem::privAdjustUsedAfterRemove(Used* const pUsed)
{
	Heap* pHeap = this->poHeap;
	if (pUsed->pPrev == nullptr && pUsed->pNext == nullptr)
	{
		pHeap->pUsedHead = nullptr;
	}
	else if (pUsed->pPrev == nullptr)
	{
		pHeap->pUsedHead = pUsed->pNext;
		pUsed->pNext->pPrev = nullptr;
	}
	else if (pUsed->pNext == nullptr)
	{
		pUsed->pPrev->pNext = nullptr;
	}
	else
	{
		pUsed->pNext->pPrev = pUsed->pPrev;
		pUsed->pPrev->pNext = pUsed->pNext;
	}
}

void Mem::privCheckOnlyOneFree()
{
	if (this->poHeap->pFreeHead)
	{
		if (this->poHeap->pFreeHead->pNext == this->poHeap->pFreeHead) this->poHeap->pFreeHead->pNext = nullptr;
		if (this->poHeap->pFreeHead->pPrev == this->poHeap->pFreeHead) this->poHeap->pFreeHead->pPrev = nullptr;
	}
}


void Mem::privCheckOnlyOneUsed()
{
	if (this->poHeap->pUsedHead)
	{
		if (this->poHeap->pUsedHead->pNext == this->poHeap->pUsedHead) this->poHeap->pUsedHead->pNext = nullptr;
		if (this->poHeap->pUsedHead->pPrev == this->poHeap->pUsedHead) this->poHeap->pUsedHead->pPrev = nullptr;
	}
}

Free* Mem::privSetPNextFit() const
{
	if (this->poHeap->pFreeHead->pNext == nullptr)return this->poHeap->pFreeHead;
	else return this->poHeap->pNextFit;
}
// --- End of File ---
