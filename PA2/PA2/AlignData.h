//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ALIGN_DATA_H
#define ALIGN_DATA_H

// -----------------------------------------------------------
// Add default constructor to each structure
// Initialize all variables to 0
// Do NOT rearrange any data layout...
// These are the classes used with Align::PrintMe();
// -----------------------------------------------------------

struct A
{
// Hint add the default constructor and set variables to zero
	int  a0;
	char a1;
	A();
};

struct B
{
	float b0;
	float b1;
	bool  b2;
	float b3;
	B();
};

struct C
{
	char   c0;
	double c1;
	char   c2;
	C();
};

struct D
{
	A      d0; // 8bytes
	double d1; // 8bytes
	B      d2; // 16bytes
	char   d3; // 1byte
	C      d4; // 24bytes
	D();
};

struct E
{
	A    a0; // 8bytes
	C    c0; // 24byts
	char aa; // 1byte
	B    b0; // 16bytes
	E();
};

#endif

// ---  End of File ---

