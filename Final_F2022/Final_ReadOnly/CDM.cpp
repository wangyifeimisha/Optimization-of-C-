//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CDM.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

CDM::CDM()
	: sqrtCount(0)
{
}

CDM *CDM::GetInstance()
{
	static CDM instance;
	return &instance;
}

int CDM::GetSqrtCount()
{
	CDM *pCDM = CDM::GetInstance();

	return pCDM->sqrtCount;
}

float CDM::Sqrt(float x)
{
	CDM *pCDM = CDM::GetInstance();
	pCDM->sqrtCount++;

	float val = sqrtf(x);

	return val;
}

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

// ---  End of File ---

