//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PerformanceTest.h"

Matrix_M_SIMD matrix_SIMD_test()
{
	Vect_M_SIMD VA0(0.556670f, -0.321394f, -0.766044f, 0.000000f);
	Vect_M_SIMD VA1(0.696747f,  0.682796f,  0.219846f, 0.000000f);
	Vect_M_SIMD VA2(0.452395f, -0.656121f,  0.604023f, 0.000000f);
	Vect_M_SIMD VA3(1.000000f,  2.000000f,  3.000000f, 1.000000f);
		
	Vect_M_SIMD VB0(-0.01f, -0.02f, -0.03f, -0.04f);
	Vect_M_SIMD VB1( 0.04f,  0.05f,  0.06f,  0.07f);
	Vect_M_SIMD VB2( 0.01f,  0.02f,  0.03f,  0.04f);
	Vect_M_SIMD VB3(-0.04f, -0.03f, -0.02f, -0.01f);

	Matrix_M_SIMD A(VA0, VA1, VA2, VA3);
	Matrix_M_SIMD B(VB0, VB1, VB2, VB3);
	Matrix_M_SIMD C = B;
		   
	for (int i = 0; i < MATRIX_COUNT; i++)
	{
		C = C * A;
	}
	return C;
}

// ---  End of File ---------------
