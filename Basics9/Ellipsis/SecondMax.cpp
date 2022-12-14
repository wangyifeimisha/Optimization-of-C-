//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include <vector>
#include <algorithm>
#include <cstdarg>
#include "SecondMax.h"

int SecondMax(int count, ...)
{
	// Do your magic here:
	va_list list;
	va_start(list, count);

	int max = 0;
	int secondMax = 0;

	for (int i = 0; i < count; i++)
	{
		int tmp;
		tmp = va_arg(list, int);
		if (tmp > max)
		{
			secondMax = max;
			max = tmp;
		}
		if (tmp > secondMax && tmp < max)
		{
			secondMax = tmp;
		}
	}

	va_end(list);
	return secondMax;
}

// ---  End of File ---------------
