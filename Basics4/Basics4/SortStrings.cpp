//--------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "SortStrings.h"

int cmp(const void* s1, const void* s2)
{
	const char** a = (const char**)s1;
	const char** b = (const char**)s2;
	return strcmp(*a, *b);
}

int cmpByWordLength(const void* s1, const void* s2)
{
	const char** a = (const char**)s1;
	const char** b = (const char**)s2;
	if (strlen(*a) == strlen(*b)) return strcmp(*a, *b);
	if ((strlen(*a) < strlen(*b))) return -1;
	else return 1;
}

void ReorderAlphabetical(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on alphabetical order, (a begin, z end)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) YOU need to use qsort() - might be a good function to know
	
	unsigned int numToken= 0;
	unsigned int i = 0;
	
	size_t length = strlen(inString);
	char* temp = new char[length + 1]();
	strcpy_s(temp, length + 1, inString);
	char* temp2 = new char[length + 1]();
	strcpy_s(temp2, length + 1, inString);
	char* temp3 = new char[length + 1]();

	// get the first demension length of char**
	while (strtok_s('\0', " ", &temp))
	{
		numToken++;
	}

	// new
	char** tokenArray = new char* [numToken]();
	
	// copy instring elements into char**
	while (i < numToken)
	{
		tokenArray[i] = strtok_s('\0', " ", &temp2);
		i++;
	}

	// sort
	qsort(tokenArray, numToken , sizeof(char*), cmp);

	// put sorted elements into string temp3
	unsigned int j;
	for (j = 0; j < numToken - 1; j++)
	{
		strcat_s(temp3, length+1 , tokenArray[j]);
		strcat_s(temp3, length+1 , " ");
	}
	strcat_s(temp3, length+1 , tokenArray[j]);

	// copy temp3 into outstring
	unsigned int index = 0;
	while (index < strlen(temp3))
	{
		outString[index] = temp3[index];
		index++;
	}
	outString[index] = '\0';

	// after strtoks the value store in temp will change so fix it back
	temp -= length;
	temp2 -= length;
	
	// delete new
	delete[]tokenArray;
	delete temp;
	delete temp2;
	delete temp3;

}



void ReorderWordLength(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on their word length order, (short, longest)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) You need to use qsort() - might be a good function to know
	unsigned int numToken = 0;
	unsigned int i = 0;

	size_t length = strlen(inString);
	char* temp = new char[length + 1]();
	strcpy_s(temp, length + 1, inString);
	char* temp2 = new char[length + 1]();
	strcpy_s(temp2, length + 1, inString);
	char* temp3 = new char[length + 1]();

	// get the first demension length of char**
	while (strtok_s('\0', " ", &temp))
	{
		numToken++;
	}

	// new
	char** tokenArray = new char* [numToken]();

	// copy instring elements into char**
	while (i < numToken)
	{
		tokenArray[i] = strtok_s('\0', " ", &temp2);
		i++;
	}

	// sort
	qsort(tokenArray, numToken, sizeof(char*), cmpByWordLength);

	// put sorted elements into string temp3
	unsigned int j;
	for (j = 0; j < numToken - 1; j++)
	{
		strcat_s(temp3, length + 1, tokenArray[j]);
		strcat_s(temp3, length + 1, " ");
	}
	strcat_s(temp3, length + 1, tokenArray[j]);

	// copy temp3 into outstring
	unsigned int index = 0;
	while (index < strlen(temp3))
	{
		outString[index] = temp3[index];
		index++;
	}
	outString[index] = '\0';

	// after strtoks the value store in temp will change so fix it back
	temp -= length;
	temp2 -= length;

	// delete new
	delete[]tokenArray;
	delete temp;
	delete temp2;
	delete temp3;
}


// ---  End of File ---
