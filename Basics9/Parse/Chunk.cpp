//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Chunk.h"

// Add code here... if desired
int checkType(char* type)
{
	if (strcmp(type, "VERTS_TYPE") == 0) return 0;
	else if (strcmp(type, "NORMS_TYPE") == 0) return 0;
	else if (strcmp(type, "ANIM_TYPE") == 0) return 0;
	else if (strcmp(type, "TEXTURE_TYPE") == 0) return 0;
	else if (strcmp(type, "UV_TYPE") == 0) return 0;
	else return -1;
}

int checkName(char* name)
{
	return (strlen(name) < 20) ? 0 : -1;
}
// ---  End of File ---------------

