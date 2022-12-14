//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "CopyingStrings.h"

char *StringCopy_1( char * const dest, const char * const input)
{
	// using strcpy()
	strcpy_s(dest, strlen(input) + 1, input);
	return dest;
}

char *StringCopy_2( char  * const dest, const char * const input)
{
	// using memcpy() and strlen()
	memcpy(dest, input, strlen(input) + 1);
	return dest;
}

char *StringCopy_3( char  * const dest, const char * const input)
{
	// using char by char copies
	size_t i;
	for (i = 0; i < strlen(input); ++i) {

		dest[i] = input[i];
	}
	dest[i] = '\0';
	return dest;
}


// ---  End of File ---
