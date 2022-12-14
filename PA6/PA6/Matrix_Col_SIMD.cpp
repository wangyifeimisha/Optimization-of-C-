//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Col_SIMD.h"
#include "Matrix_Col_SIMD.h"

Matrix_Col_SIMD::Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
								 const Vect_Col_SIMD &tV1,
								 const Vect_Col_SIMD &tV2,
								 const Vect_Col_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

//Vect_Col_SIMD Matrix_Col_SIMD::operator * (const Vect_Col_SIMD &vb)
//{
//	AZUL_REPLACE_ME(vb);
//	return Vect_Col_SIMD();
//}

//Matrix_Col_SIMD Matrix_Col_SIMD::operator * (const Matrix_Col_SIMD &mb)
//{
//	AZUL_REPLACE_ME(mb);
//	return Matrix_Col_SIMD();
//}

MMMMMV::operator Vect_Col_SIMD()
{
	Vect_Col_SIMD A;
	Vect_Col_SIMD B;
	Vect_Col_SIMD C;
	Vect_Col_SIMD D;

	A._m = _mm_mul_ps(this->m4.v0._m, this->v0._m);
	B._m = _mm_mul_ps(this->m4.v1._m, this->v0._m);
	A._m = _mm_hadd_ps(A._m, B._m);
	B._m = _mm_mul_ps(this->m4.v2._m, this->v0._m);
	C._m = _mm_mul_ps(this->m4.v3._m, this->v0._m);
	B._m = _mm_hadd_ps(B._m, C._m);
	C._m = _mm_hadd_ps(A._m, B._m);

	A._m = _mm_mul_ps(this->m3.v0._m, C._m);
	B._m = _mm_mul_ps(this->m3.v1._m, C._m);
	A._m = _mm_hadd_ps(A._m, B._m);
	B._m = _mm_mul_ps(this->m3.v2._m, C._m);
	D._m = _mm_mul_ps(this->m3.v3._m, C._m);
	B._m = _mm_hadd_ps(B._m, D._m);
	C._m = _mm_hadd_ps(A._m, B._m);

	A._m = _mm_mul_ps(this->m2.v0._m, C._m);
	B._m = _mm_mul_ps(this->m2.v1._m, C._m);
	A._m = _mm_hadd_ps(A._m, B._m);
	B._m = _mm_mul_ps(this->m2.v2._m, C._m);
	D._m = _mm_mul_ps(this->m2.v3._m, C._m);
	B._m = _mm_hadd_ps(B._m, D._m);
	C._m = _mm_hadd_ps(A._m, B._m);

	A._m = _mm_mul_ps(this->m1.v0._m, C._m);
	B._m = _mm_mul_ps(this->m1.v1._m, C._m);
	A._m = _mm_hadd_ps(A._m, B._m);
	B._m = _mm_mul_ps(this->m1.v2._m, C._m);
	D._m = _mm_mul_ps(this->m1.v3._m, C._m);
	B._m = _mm_hadd_ps(B._m, D._m);
	C._m = _mm_hadd_ps(A._m, B._m);

	A._m = _mm_mul_ps(this->m0.v0._m, C._m);
	B._m = _mm_mul_ps(this->m0.v1._m, C._m);
	A._m = _mm_hadd_ps(A._m, B._m);
	B._m = _mm_mul_ps(this->m0.v2._m, C._m);
	D._m = _mm_mul_ps(this->m0.v3._m, C._m);
	B._m = _mm_hadd_ps(B._m, D._m);
	C._m = _mm_hadd_ps(A._m, B._m);
	return C;
}

// ---  End of File ---------------
