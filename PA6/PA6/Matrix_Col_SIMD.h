//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Matrix_Col_SIMD_H
#define Matrix_Col_SIMD_H

#include "Vect_Col_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    Implement for Col Major
//    No implementation in Header
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline MM operator * (const Matrix_Col_SIMD &m, const Matrix_Col_SIMD &n)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Matrix_Col_SIMD
{
public:
	Matrix_Col_SIMD() = default;
	Matrix_Col_SIMD(const Matrix_Col_SIMD &tmp) = default;
	Matrix_Col_SIMD &operator=(const Matrix_Col_SIMD &tmp) = default;
	~Matrix_Col_SIMD() = default;

	Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
					const Vect_Col_SIMD &tV1,
					const Vect_Col_SIMD &tV2,
					const Vect_Col_SIMD &tV3);
 
	//Matrix_Col_SIMD operator * (const Matrix_Col_SIMD &n);
	//Vect_Col_SIMD operator * (const Vect_Col_SIMD &n);

	union
	{
		struct
		{
			Vect_Col_SIMD v0;
			Vect_Col_SIMD v1;
			Vect_Col_SIMD v2;
			Vect_Col_SIMD v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};


struct MM
{
	const Matrix_Col_SIMD& m0;
	const Matrix_Col_SIMD& m1;

	MM(const Matrix_Col_SIMD& m0, const Matrix_Col_SIMD& m1)
		: m0(m0), m1(m1)
	{
	};

};

inline MM operator * (const Matrix_Col_SIMD& m, const Matrix_Col_SIMD& n)
{
	return MM(m, n);
}

struct MMM
{
	const Matrix_Col_SIMD& m0;
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	
	MMM(const MM& m, const Matrix_Col_SIMD& m2)
		: m0(m.m0), m1(m.m1), m2(m2)
	{
	};

};

inline MMM operator * (const MM& m, const Matrix_Col_SIMD& n)
{
	return MMM(m, n);
}

struct MMMM
{
	const Matrix_Col_SIMD& m0;
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	
	MMMM(const MMM& m, const Matrix_Col_SIMD& m3)
		: m0(m.m0), m1(m.m1), m2(m.m2), m3(m3)
	{
	};

};

inline MMMM operator * (const MMM& m, const Matrix_Col_SIMD& n)
{
	return MMMM(m, n);
}

struct MMMMM
{
	const Matrix_Col_SIMD& m0;
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	const Matrix_Col_SIMD& m4;

	MMMMM(const MMMM& m, const Matrix_Col_SIMD& m4)
		: m0(m.m0), m1(m.m1), m2(m.m2), m3(m.m3), m4(m4)
	{
	};

};

inline MMMMM operator * (const MMMM& m, const Matrix_Col_SIMD& n)
{
	return MMMMM(m, n);
}

struct MMMMMV
{
	const Matrix_Col_SIMD& m0;
	const Matrix_Col_SIMD& m1;
	const Matrix_Col_SIMD& m2;
	const Matrix_Col_SIMD& m3;
	const Matrix_Col_SIMD& m4;
	const Vect_Col_SIMD& v0;

	MMMMMV(const MMMMM& m, const Vect_Col_SIMD& v0)
		: m0(m.m0), m1(m.m1), m2(m.m2), m3(m.m3), m4(m.m4), v0(v0)
	{
	};

	operator Vect_Col_SIMD();
};

inline MMMMMV operator * (const MMMMM& m, const Vect_Col_SIMD& n)
{
	return MMMMMV(m, n);
}
#endif

// ---  End of File ---------------
