#include "Matrix3x3.h"
#include "MacroConfig.h"
#include "Matrix4x4.h"

#include <memory.h>
#include <math.h>


namespace cxMatrix
{

	Matrix3x3* MCreate3x3(Matrix3x3* pOut)
	{
		memset(pOut->mat,0,sizeof(float) * MATRIX_3X3_SIZE);
		return pOut;
	}

	Matrix3x3* MLoadIdentity3x3( Matrix3x3* pOut )
	{
		MCreate3x3(pOut);
		pOut->mat[0] = pOut->mat[4] = pOut->mat[8] = 1.0f;
		return pOut;
	}

	Matrix3x3* MMult3x3( Matrix3x3* pOut,Matrix3x3* mat1,Matrix3x3* mat2 )
	{
		float mat[9];
		const float *m1 = mat1->mat, *m2 = mat2->mat;

		mat[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
		mat[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
		mat[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];

		mat[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
		mat[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
		mat[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];

		mat[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
		mat[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
		mat[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];

		memcpy(pOut->mat, mat, sizeof(float)*MATRIX_3X3_SIZE);

		return pOut;
	}

	Matrix3x3* MCopy3x3( Matrix3x3* pOut,Matrix3x3* pIn )
	{
		do 
		{
			BREAK_IF(pOut == pIn);
			memcpy(pOut,pIn,sizeof(float) * MATRIX_3X3_SIZE);
		} while (0);
		return pOut;
	}



}