//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Mem.h"

//--------------------------------
//    DO NOT MODIFY this File
//---------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 

TEST(Mem7_Allocate_3_Top_down_free, TestConfig::Flag::ALL)
{
#if Mem7_Allocate_3_Top_down_free	

	{
		FileIO::Open("Student_", "Test_07");

		fprintf(FileIO::GetHandle(), "Test7: \n\n");

		fprintf(FileIO::GetHandle(), " 1) used                  \n");
		fprintf(FileIO::GetHandle(), " 2) used                  \n");
		fprintf(FileIO::GetHandle(), " 3) used                  \n");
		fprintf(FileIO::GetHandle(), " 4) top down free         \n\n");
		fprintf(FileIO::GetHandle(), "     Mem mem(Mem::Guard::Type_A); \n");
		fprintf(FileIO::GetHandle(), "     mem.initialize();                     \n");
		fprintf(FileIO::GetHandle(), "    mem.Print(1);                          \n");
		fprintf(FileIO::GetHandle(), "     void *a = mem.malloc( 0x200 );        \n");
		fprintf(FileIO::GetHandle(), "    mem.Print(2);                          \n");
		fprintf(FileIO::GetHandle(), "     void *b = mem.malloc( 0x200 );        \n");
		fprintf(FileIO::GetHandle(), "    mem.Print(3);                          \n");
		fprintf(FileIO::GetHandle(), "     void *c = mem.malloc( 0x200 );        \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(4);                         \n");
		fprintf(FileIO::GetHandle(), "     mem.free( a );                        \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(5);                         \n");
		fprintf(FileIO::GetHandle(), "     mem.free( b );                        \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(6);                         \n");
		fprintf(FileIO::GetHandle(), "     mem.free( c );                        \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(7);                         \n");

		// Part A:
		Mem mem1(Mem::Guard::Type_A);
		mem1.initialize();
		mem1.Print(1);

		void *a1 = mem1.malloc(0x200);
		mem1.Print(2);

		void *b1 = mem1.malloc(0x200);
		mem1.Print(3);

		void *c1 = mem1.malloc(0x200);
		mem1.Print(4);

		// Part B:
		mem1.free(a1);
		mem1.Print(5);

		// Part C:
		mem1.free(b1);
		mem1.Print(6);

		// Part D:
		mem1.free(c1);
		mem1.Print(7);

		FileIO::Close();
	}

	{
		// ----  GENERAL CHECK ------------------------------------------------------

		// ---- Part A: -------------------------------------------------------------

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();

		void *a = mem.malloc(0x200);
		void *b = mem.malloc(0x200);
		void *c = mem.malloc(0x200);

		// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x644);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x438);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 3);
		CHECK_EQUAL(h->currUsedMem, 3 * 0x200);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0xc1b0);

		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;
		uint32_t secret;

		// ---- USED HDR 1 -------------------------------------------

		// Check type
		Used *used = (Used *)(h + 1);
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x22c);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(a), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x20);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(b), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(c), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x644);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- free HDR 4 -------------------------------------------

		// Check type
		Free *free = (Free *)blkEnd;
		// Should be USED
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x644);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x650);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc1b0);

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

		// ---- Part B: -------------------------------------------------------------

		mem.free(a);

		// ---- Verify B: -----------------------------------------------------------

		h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x438);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 2);
		CHECK_EQUAL(h->currUsedMem, 0x400);

		CHECK_EQUAL(h->currNumFreeBlocks, 2);
		CHECK_EQUAL(h->currFreeMem, 0xc3b0);

		// ---- FREE HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x644);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x438);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x644);
		CHECK_EQUAL(used->mAllocSize, 0x200);


		// ---- free HDR 4 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be USED
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x644);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x650);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc1b0);

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

		// ---- Part C: -------------------------------------------------------------

		mem.free(b);

		// ---- Verify C: -----------------------------------------------------------

		h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x438);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 1);
		CHECK_EQUAL(h->currUsedMem, 0x200);

		CHECK_EQUAL(h->currNumFreeBlocks, 2);
		CHECK_EQUAL(h->currFreeMem, 0xc5bc);

		// ---- FREE HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x644);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(free->mAllocSize, 0x40C);

		// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x644);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- free HDR 3 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x644);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x650);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc1b0);

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

		// ---- Part D: -------------------------------------------------------------

		mem.free(c);

		// ---- Verify D: -----------------------------------------------------------

		h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(h->pUsedHead, nullptr);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 0);
		CHECK_EQUAL(h->currUsedMem, 0x0);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0xc7d4);

		// ---- FREE HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		// ---- free Type ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc7d4);

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));
	}

	{
		// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
		void *a = mem.malloc(0x200);
		CHECK(true);
		void *b = mem.malloc(0x200);
		CHECK(true);
		void *c = mem.malloc(0x200);
		CHECK(true);
		mem.free(a);
		CHECK(true);
		mem.free(b);
		CHECK(true);
		mem.free(c);
		CHECK(true);

	}

#endif
}  TEST_END

// ---  End of File ---
