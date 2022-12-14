//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "A.h"

void vTableQuestions_A()
{
	// Class A:  Question 0-9
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 0 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 1 , 4 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 2 , 0xFFFF );

	// 2nd jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 3 , 0xFFFF);

	// 3rd jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 4 , 0xFFFF);

	// 4th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 5 , 0xa004 );

	// 5th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 6 , 0 );

	// 6th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 7 , 0 );

	// 7th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 8 , 0 );

	// 8th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 9 , 0 );

}

// ---  End of File ---------------
