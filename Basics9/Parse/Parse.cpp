//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Parse.h"
#include "Chunk.h"
// Add helper function/classes here if you desire
int parse(int argc, char* argv[])
{
	if (argc != 5)
	{
		return -1;
	}


	if ((strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-T") == 0) &&
		(strcmp(argv[3], "-n") == 0 || strcmp(argv[3], "-N") == 0))
	{
		if (checkType(argv[2]) == 0 && checkName(argv[4]) == 0)
		{
			return 0;
		}
		return -1;
	}

	if ((strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-N") == 0) &&
		(strcmp(argv[3], "-t") == 0 || strcmp(argv[3], "-T") == 0))
	{
		if (checkName(argv[2]) == 0 && checkType(argv[4]) == 0)
		{
			return 0;
		}
		else return -1;
	}

	return -1;
}

// ---  End of File ---------------

