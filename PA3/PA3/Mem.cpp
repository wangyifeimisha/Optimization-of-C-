//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
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
	
	Heap* pHeap = this->GetHeap();

	// Find Free block
	Free* availFree = this->privFindFreeBlock(_size);

	Free* availpNext = availFree->pNext;
	Free* availpPrev = availFree->pPrev;
	uint32_t availFreeSize = (uint32_t)availFree->mAllocSize;

	// Create Used block
	Used* startUsed = (Used*)availFree;
	Used* pUsed = new (startUsed)Used(_size);

	// Add used to front
	this->privAddUsedToFront(pUsed);

	uint32_t restSize = availFreeSize - (uint32_t)pUsed->mAllocSize;

	// Perfect fit
	if (restSize == 0)
	{
		pHeap->currNumUsedBlocks++;
		pHeap->currUsedMem += _size;
		pHeap->currNumFreeBlocks--;
		pHeap->currFreeMem -= _size;

		this->privAdjustFreeAfterRemove(availFree);
		pHeap->pNextFit = pHeap->pFreeHead;
	}
	else if (restSize < sizeof(Free))
	{
		// Ignore
	}
	else
	{
		pHeap->currNumUsedBlocks++;
		pHeap->currUsedMem += (uint32_t)_size;
		pHeap->currFreeMem -= _size + sizeof(Free);

		// Subdivide Free block
		Free* startFree = (Free*)((uint32_t)pUsed + _size + sizeof(Used));
		Free* pFree = new (startFree)Free(restSize);
		
		pFree->mAllocSize = (uint16_t)(restSize - sizeof(Free));
		pFree->pPrev = availpPrev;
		pFree->pNext = availpNext;

		this->privAdjustFreeAfterSubdivide(pFree);

		pHeap->pNextFit = pFree;
	
	}
	return (pUsed+1);

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
	
	Heap* pHeap = this->GetHeap();

	// Find Used block then remove
	Used* pUsed = this->privFindUsedBlock(data);

	bool bAboveFree = (bool)pUsed->bAboveFree;

	this->privAdjustUsedAfterRemove(pUsed);

	// Create Free block
	Free* startFree = (Free*)pUsed;
	Free* pFree = new (startFree)Free(pUsed->mAllocSize);

	pHeap->currNumUsedBlocks--;
	pHeap->currUsedMem -= pUsed->mAllocSize;
	pHeap->currFreeMem += pFree->mAllocSize;
	pHeap->currNumFreeBlocks++;

	// Start handle coalescing of Free
	if ((uint32_t)pFree == (uint32_t)(pHeap+1))
	{
		// Handle Free in poHeap ... reset pFreeHead
		if (pHeap->pFreeHead != nullptr)
		{
			pHeap->pFreeHead->pPrev = pFree;
		}
		pFree->pNext = pHeap->pFreeHead;
		pHeap->pFreeHead = pFree;
	}
	else if (bAboveFree)
	{
		// Implement in PA4
	}

	pHeap->pNextFit = pHeap->pFreeHead;

	uint32_t nextBlockAddr = (uint32_t)pFree + sizeof(Free) + pFree->mAllocSize;

	Type nextBlockType = ((Free*)nextBlockAddr)->mType;
	if ((int)nextBlockType == (int)Type::FREE_Type)
	{
		Free* nextBlock = (Free*)(((uint32_t)pFree + sizeof(Free) + pFree->mAllocSize));
		pFree = this->privCoalescingFree(pFree, nextBlock);
	}
	else if (nextBlockType == Type::USED_Type)
	{
		Used* nextBlock = (Used*)(((uint32_t)pFree + sizeof(Free) + pFree->mAllocSize));
		nextBlock->bAboveFree = true;
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
	return pFreeFound;
}

void Mem::privAddUsedToFront(Used* const pUsed)
{
	Heap* pHeap = this->GetHeap();
	pUsed->pPrev = nullptr;
	pUsed->pNext = pHeap->pUsedHead;
	if (pHeap->pUsedHead != nullptr)
	{
		pHeap->pUsedHead->pPrev = pUsed;
	}
	pHeap->pUsedHead = pUsed;
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

Free* Mem::privCoalescingFree(Free* pFree1, Free* pFree2)
{
	Heap* pHeap = this->GetHeap();

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
void Mem::privAdjustFreeAfterRemove(const Free* pFree)
{
	Heap* pHeap = this->GetHeap();
	if (pFree->pNext == nullptr && pFree->pPrev == nullptr)
	{
		pHeap->pFreeHead = nullptr;
	}
	else if (pFree->pPrev == nullptr)
	{
		pHeap->pFreeHead = pFree->pNext;
		pFree->pNext->pPrev = nullptr;
	}
	else if (pFree->pNext == nullptr)
	{
		pFree->pPrev->pNext = nullptr;
	}
	else
	{
		pFree->pPrev->pNext = pFree->pNext;
		pFree->pNext->pPrev = pFree->pPrev;
	}
}

void Mem::privAdjustFreeAfterSubdivide(Free* const pFree)
{
	Heap* pHeap = this->GetHeap();
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


void Mem::privAdjustUsedAfterRemove(const Used* pUsed)
{
	Heap* pHeap = this->GetHeap();
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
// --- End of File ---
