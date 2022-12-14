//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"

#include "Language.h"
#include "Compiler.h"

TEST_WITH_TEARDOWN(MemoryLeak_Test_Enable, TestConfig::ALL)
{
#if MemoryLeak_Test_Enable

	// PLACE HOLDER - you don't get TESTS for your FINAL!
	CHECK(true);
	
#endif
} TEST_END


TEST_TEARDOWN(MemoryLeak_Test_Enable)
{

}


// ---  End of File ---

