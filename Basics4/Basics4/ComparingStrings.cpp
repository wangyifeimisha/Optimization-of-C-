//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "ComparingStrings.h"

int StringCompare_1( const char  * const s1, const char * const s2)
{
	// using strcmp()
	int result = strcmp(s1, s2);
	return result;
}

int StringCompare_2( const char  * const s1, const char * const s2)
{
	// using memcmp() & strlen()
	int result = 0;
	result = memcmp(s1, s2, strlen(s1));
	return result;
}

int StringCompare_3( const char  * const s1, const char * const s2)
{
	// using char by char comparisions
	int result = 0;
	for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] == s2[i]) continue;
		else result = s1[i] < s2[i] ? -1 : 1;
	}
	return result;
}


// ---  End of File ---
