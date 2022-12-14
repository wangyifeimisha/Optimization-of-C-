//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"

Vect_Row_SIMD::Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Row_SIMD Vect_Row_SIMD::operator * ( const Matrix_Row_SIMD &ma)
{
	// replace everything... 
	// stub to shut up warnings
	Vect_Row_SIMD A;
	Vect_Row_SIMD B;
	A._m = _mm_set1_ps(this->x);
	B._m = _mm_mul_ps(A._m, ma.v0._m);
	A._m = _mm_set1_ps(this->y);
	B._m = _mm_add_ps(B._m, _mm_mul_ps(A._m, ma.v1._m));
	A._m = _mm_set1_ps(this->z);
	B._m = _mm_add_ps(B._m, _mm_mul_ps(A._m, ma.v2._m));
	A._m = _mm_set1_ps(this->w);
	B._m = _mm_add_ps(B._m, _mm_mul_ps(A._m, ma.v3._m));
	return B;
	
};


// ---  End of File ---------------


