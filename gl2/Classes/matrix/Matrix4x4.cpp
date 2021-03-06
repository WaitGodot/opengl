#include "Matrix4x4.h"
#include <memory>
#include <assert.h>
#include <math.h>
#include "Vector3.h"
#include "Matrix3x3.h"

namespace cxMatrix
{

	Matrix4x4* MLoadIdentity4x4(Matrix4x4* pOut)
	{
		Matrix4x4* mat = MCreate4x4(pOut);
		mat->mat[0] = mat->mat[5] = mat->mat[10] = mat->mat[15] = 1;
		return mat;
	}

	Matrix4x4* MCreate4x4(Matrix4x4* pOut)
	{
		//matrix4* mat = new matrix4();
		memset(pOut->mat,0,MATRIX_4X4_SIZE * sizeof(float));
		return pOut;
	}

	Matrix4x4* MMult4x4( Matrix4x4* pOut,Matrix4x4* mat1,Matrix4x4* mat2 )
	{
		assert( mat1!= NULL && mat2 != NULL,"mult,input mat error!");
		
		float mat[MATRIX_4X4_SIZE];

		mat[0] = mat1->mat[0]*mat2->mat[0] + mat1->mat[4]*mat2->mat[1] +mat1->mat[8]*mat2->mat[2] + mat1->mat[12]*mat2->mat[3];
		mat[1] = mat1->mat[1]*mat2->mat[0] + mat1->mat[5]*mat2->mat[1] +mat1->mat[9]*mat2->mat[2] + mat1->mat[13]*mat2->mat[3];
		mat[2] = mat1->mat[2]*mat2->mat[0] + mat1->mat[6]*mat2->mat[1] +mat1->mat[10]*mat2->mat[2] + mat1->mat[14]*mat2->mat[3];
		mat[3] = mat1->mat[3]*mat2->mat[0] + mat1->mat[7]*mat2->mat[1] +mat1->mat[11]*mat2->mat[2] + mat1->mat[15]*mat2->mat[3];
		mat[4] = mat1->mat[0]*mat2->mat[4] + mat1->mat[4]*mat2->mat[5] +mat1->mat[8]*mat2->mat[6] + mat1->mat[12]*mat2->mat[7];
		mat[5] = mat1->mat[1]*mat2->mat[4] + mat1->mat[5]*mat2->mat[5] +mat1->mat[9]*mat2->mat[6] + mat1->mat[13]*mat2->mat[7];
		mat[6] = mat1->mat[2]*mat2->mat[4] + mat1->mat[6]*mat2->mat[5] +mat1->mat[10]*mat2->mat[6] + mat1->mat[14]*mat2->mat[7];
		mat[7] = mat1->mat[3]*mat2->mat[4] + mat1->mat[7]*mat2->mat[5] +mat1->mat[11]*mat2->mat[6] + mat1->mat[15]*mat2->mat[7];
		mat[8] = mat1->mat[0]*mat2->mat[8] + mat1->mat[4]*mat2->mat[9] +mat1->mat[8]*mat2->mat[10] + mat1->mat[12]*mat2->mat[11];
		mat[9] = mat1->mat[1]*mat2->mat[8] + mat1->mat[5]*mat2->mat[9] +mat1->mat[9]*mat2->mat[10] + mat1->mat[13]*mat2->mat[11];
		mat[10] = mat1->mat[2]*mat2->mat[8] + mat1->mat[6]*mat2->mat[9] +mat1->mat[10]*mat2->mat[10] + mat1->mat[14]*mat2->mat[11];
		mat[11] = mat1->mat[3]*mat2->mat[8] + mat1->mat[7]*mat2->mat[9] +mat1->mat[11]*mat2->mat[10] + mat1->mat[15]*mat2->mat[11];
		mat[12] = mat1->mat[0]*mat2->mat[12] + mat1->mat[4]*mat2->mat[13] +mat1->mat[8]*mat2->mat[14] + mat1->mat[12]*mat2->mat[15];
		mat[13] = mat1->mat[1]*mat2->mat[12] + mat1->mat[5]*mat2->mat[13] +mat1->mat[9]*mat2->mat[14] + mat1->mat[13]*mat2->mat[15];
		mat[14] = mat1->mat[2]*mat2->mat[12] + mat1->mat[6]*mat2->mat[13] +mat1->mat[10]*mat2->mat[14] + mat1->mat[14]*mat2->mat[15];
		mat[15] = mat1->mat[3]*mat2->mat[12] + mat1->mat[7]*mat2->mat[13] +mat1->mat[11]*mat2->mat[14] + mat1->mat[15]*mat2->mat[15];

		memcpy(pOut->mat,mat,sizeof(float)*MATRIX_4X4_SIZE);

		return pOut;
	}

	Matrix4x4* MCopy4x4( Matrix4x4* pOut,Matrix4x4* pIn )
	{
		if( pOut == pIn){
			return pOut;
		}

		memcpy(pOut->mat, pIn->mat, sizeof(float)*MATRIX_4X4_SIZE);
		return pOut;
	}

	Matrix4x4* MTranslatef4x4( Matrix4x4* pOut,float x,float y,float z )
	{
		MLoadIdentity4x4(pOut);
		pOut->mat[12] = x;
		pOut->mat[13] = y;
		pOut->mat[14] = z;
		return pOut;
	}

	Matrix4x4* MRotatef4x4( Matrix4x4* pOut,float degree,float x, float y ,float z )
	{
		MLoadIdentity4x4(pOut);
		// normalize vector
		Vector3 vec(x,y,z);
		
		vec.normalize();
		x = vec.x;
		y = vec.y;
		z = vec.z;

		float rcos = cosf(degree);
		float rsin = sinf(degree);

		// rotate matrix
		pOut->mat[0] = rcos + (1 - rcos)*x*x;
		pOut->mat[1] = (1 - rcos)*y*x + rsin*z;
		pOut->mat[2] = (1 - rcos)*x*z - rsin*y;
		pOut->mat[3] = 0.0f;

		pOut->mat[4] = (1-rcos)*x*y - rsin*z;
		pOut->mat[5] = rcos + (1 - rcos)*y*y;
		pOut->mat[6] = (1 - rcos)*y*z + rsin*x;
		pOut->mat[7] = 0.0f;

		pOut->mat[8] = (1 - rcos)*x*z + rsin*y;
		pOut->mat[9] = (1 - rcos)*y*z - rsin*x;
		pOut->mat[10] = rcos + (1 - rcos)*z*z;
		pOut->mat[11] = 0.0f;

		pOut->mat[12] = pOut->mat[13] = pOut->mat[14] = 0.0f;
		pOut->mat[15] = 1.0f;
		return pOut;

	}

	Matrix4x4* MScalef4x4( Matrix4x4* pOut,float x,float y,float z )
	{
		MLoadIdentity4x4(pOut);
		pOut->mat[0] = x;
		pOut->mat[5] = y;
		pOut->mat[10] = z;

		return pOut;
	}

	Matrix3x3* MMat4ExtractRotation( Matrix3x3* pOut,Matrix4x4* pIn )
	{
		pOut->mat[0] = pIn->mat[0];
		pOut->mat[1] = pIn->mat[1];
		pOut->mat[2] = pIn->mat[2];

		pOut->mat[3] = pIn->mat[4];
		pOut->mat[4] = pIn->mat[5];
		pOut->mat[5] = pIn->mat[6];

		pOut->mat[6] = pIn->mat[8];
		pOut->mat[7] = pIn->mat[9];
		pOut->mat[8] = pIn->mat[10];

		return pOut;
	}

	Matrix4x4* MMat3TransformMat4( Matrix4x4* pOut,Matrix3x3* pIn )
	{
		pOut->mat[0] = pIn->mat[0];
		pOut->mat[1] = pIn->mat[1];
		pOut->mat[2] = pIn->mat[2];
		pOut->mat[3] = 0.0F;

		pOut->mat[4] = pIn->mat[3];
		pOut->mat[5] = pIn->mat[4];
		pOut->mat[6] = pIn->mat[5];
		pOut->mat[7] = 0.0f;

		pOut->mat[8] = pIn->mat[6];
		pOut->mat[9] = pIn->mat[7];
		pOut->mat[10] = pIn->mat[8];
		pOut->mat[11] = 0.0f;

		pOut->mat[12] = 0.0f;
		pOut->mat[13] = 0.0f;
		pOut->mat[14] = 0.0f;
		pOut->mat[15] = 1.0f;

		return pOut;
	}

}