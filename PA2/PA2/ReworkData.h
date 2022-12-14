//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef REWORK_DATA_H
#define REWORK_DATA_H

struct DataA	// 16bytes
{
	double r;
	char a;
	char b;
	char pad0;
	char pad1;
	char pad2;
	char pad3;
	char pad4;
	char pad5;
};

struct DataB	// 24bytes
{
	DataA da;
	int i;
	char a;
	char b;
	char pad0;
	char pad1;
};

struct DataC	// 12bytes
{
	int j;
	int i;
	bool f;
	char a;
	char pad0;
	char pad1;
};

struct DataD	// 16bytes
{
	double r;
	int i;
	char a;
	char b;
	char pad0;
	char pad1;
};

struct DataE	// 32bytes
{
	double r;
	int x;
	char name[12]; 
	int* p;
	char a;
	char c;
	char pad0;
	char pad1;
};

struct Vect		// 20bytes
{
	float vx;
	float vy;	
	float vz;
	float vw;
	char b;
	char a;
	char pad0;
	char pad1;
};

struct DataF	// 32bytes
{
	Vect v;
	int i;
	int j;
	char c;
	char b;
	char pad0;
	char pad1;
};

struct DataG	// 56bytes
{
	Vect  v;	//20
	char  c0;
	char  b0;
	char pad0;
	char pad1;
	DataA a0;	//16
	double d1;	//8
	double d0;	//8
};



#endif

// ---  End of File ---

