//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include"LengthOfStrings.h"

size_t LengthOfString_1( const char  * const input)
{
	// using strlen()
	size_t result = strlen(input);
	return result;
}

size_t LengthOfString_2( const char  * const input)
{
	// using char by char
	size_t result = 0;
	while (input[result] != '\0')
	{
		++result;
	}
	return result;
}


// ---  End of File ---

