//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD &tV0,
							 const Vect_M_SIMD &tV1,
							 const Vect_M_SIMD &tV2,
							 const Vect_M_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD &mb) const
{
	// replace everything... 
	// stub to shut up warnings
	Matrix_M_SIMD M;

	Vect_M_SIMD A;
	Vect_M_SIMD B;
	Vect_M_SIMD C;
	Vect_M_SIMD D;
	
	A._m = _mm_set1_ps(this->v0.x);
	M.v0._m = _mm_mul_ps(A._m, mb.v0._m);
	B._m = _mm_set1_ps(this->v1.x);
	M.v1._m = _mm_mul_ps(B._m, mb.v0._m);
	C._m = _mm_set1_ps(this->v2.x);
	M.v2._m = _mm_mul_ps(C._m, mb.v0._m);
	D._m = _mm_set1_ps(this->v3.x);
	M.v3._m = _mm_mul_ps(D._m, mb.v0._m);


	A._m = _mm_set1_ps(this->v0.y);
	M.v0._m = _mm_add_ps(M.v0._m, _mm_mul_ps(A._m, mb.v1._m));
	B._m = _mm_set1_ps(this->v1.y);
	M.v1._m = _mm_add_ps(M.v1._m, _mm_mul_ps(B._m, mb.v1._m));
	C._m = _mm_set1_ps(this->v2.y);
	M.v2._m = _mm_add_ps(M.v2._m, _mm_mul_ps(C._m, mb.v1._m));
	D._m = _mm_set1_ps(this->v3.y);
	M.v3._m = _mm_add_ps(M.v3._m, _mm_mul_ps(D._m, mb.v1._m));
	

	A._m = _mm_set1_ps(this->v0.z);
	M.v0._m = _mm_add_ps(M.v0._m, _mm_mul_ps(A._m, mb.v2._m));
	B._m = _mm_set1_ps(this->v1.z);
	M.v1._m = _mm_add_ps(M.v1._m, _mm_mul_ps(B._m, mb.v2._m));
	C._m = _mm_set1_ps(this->v2.z);
	M.v2._m = _mm_add_ps(M.v2._m, _mm_mul_ps(C._m, mb.v2._m));
	D._m = _mm_set1_ps(this->v3.z);
	M.v3._m = _mm_add_ps(M.v3._m, _mm_mul_ps(D._m, mb.v2._m));


	A._m = _mm_set1_ps(this->v0.w);
	M.v0._m = _mm_add_ps(M.v0._m, _mm_mul_ps(A._m, mb.v3._m));
	B._m = _mm_set1_ps(this->v1.w);
	M.v1._m = _mm_add_ps(M.v1._m, _mm_mul_ps(B._m, mb.v3._m));
	C._m = _mm_set1_ps(this->v2.w);
	M.v2._m = _mm_add_ps(M.v2._m, _mm_mul_ps(C._m, mb.v3._m));
	D._m = _mm_set1_ps(this->v3.w);	
	M.v3._m = _mm_add_ps(M.v3._m, _mm_mul_ps(D._m, mb.v3._m));

	return M;
}


// ---  End of File ---------------
