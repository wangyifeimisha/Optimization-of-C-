//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Align.h"

//-------------------------------------------------------------
// PrintME()
//
// Write your alignment printing function here
//-------------------------------------------------------------

Align::Info Align::PrintME(void *pData, int StructSize, char *pString)
{
	// Use Trace::out2(...) to display the data layout and padding

        // NOTE:   out2() NOT out()
        //         it won't be graded without out2()

	// Mimic the KeenanSampleOutput_Debug.txt

        // EXACtLY or the grading system will give a 0
	
	assert(pString);
	assert(pData);
	
	unsigned char* p = (unsigned char *)pData;
	int pad = 0;
	int addr = 0;
	Trace::out2("%s: \n", pString);
	for (int i = 0; i < StructSize / 4; i++)
	{
		if (p[0] == 0xAA)
		{
			pad++;
		}
		if (p[1] == 0xAA)
		{
			pad++;
		}
		if (p[2] == 0xAA)
		{
			pad++;
		}
		if (p[3] == 0xAA)
		{
			pad++;
		}
		Trace::out2("  0x%02x: %02x %02x %02x %02x \n", addr, p[0], p[1], p[2], p[3]);
		p += 4;
		addr += 4;
	}
	
	Trace::out2("------------------------\n");
	Trace::out2("size : %d padding : %d \n", StructSize, pad);
	Trace::out2("\n");

	AZUL_REPLACE_ME(pData);
	AZUL_REPLACE_ME(StructSize);
	AZUL_REPLACE_ME(pString);

	Info info;
	info.NumBytesOfPadding = pad;
	info.NumTotalBytes = StructSize;

	return info;
}

// ---  End of File ---

