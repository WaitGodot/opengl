#include "matrix4.h"
#include <memory>
#include <assert.h>
#include <math.h>
#include "Vector3.h"

namespace cxMatrix
{





	matrix4* MLoadIdentity(matrix4* pOut)
	{
		matrix4* mat = MCreate(pOut);
		mat->m_mat[0] = mat->m_mat[5] = mat->m_mat[10] = mat->m_mat[15] = 1;
		return mat;
	}

	matrix4* MCreate(matrix4* pOut)
	{
		//matrix4* mat = new matrix4();
		memset(pOut->m_mat,0,MATRIXSIZE * sizeof(float));
		return pOut;
	}

	matrix4* MMult( matrix4* pOut,matrix4* mat1,matrix4* mat2 )
	{
		assert( mat1!= NULL && mat2 != NULL,"mult,input mat error!");
		
		float mat[MATRIXSIZE];

		mat[0] = mat1->m_mat[0]*mat2->m_mat[0] + mat1->m_mat[4]*mat2->m_mat[1] +mat1->m_mat[8]*mat2->m_mat[2] + mat1->m_mat[12]*mat2->m_mat[3];
		mat[1] = mat1->m_mat[1]*mat2->m_mat[0] + mat1->m_mat[5]*mat2->m_mat[1] +mat1->m_mat[9]*mat2->m_mat[2] + mat1->m_mat[13]*mat2->m_mat[3];
		mat[2] = mat1->m_mat[2]*mat2->m_mat[0] + mat1->m_mat[6]*mat2->m_mat[1] +mat1->m_mat[10]*mat2->m_mat[2] + mat1->m_mat[14]*mat2->m_mat[3];
		mat[3] = mat1->m_mat[3]*mat2->m_mat[0] + mat1->m_mat[7]*mat2->m_mat[1] +mat1->m_mat[11]*mat2->m_mat[2] + mat1->m_mat[15]*mat2->m_mat[3];
		mat[4] = mat1->m_mat[0]*mat2->m_mat[4] + mat1->m_mat[4]*mat2->m_mat[5] +mat1->m_mat[8]*mat2->m_mat[6] + mat1->m_mat[12]*mat2->m_mat[7];
		mat[5] = mat1->m_mat[1]*mat2->m_mat[4] + mat1->m_mat[5]*mat2->m_mat[5] +mat1->m_mat[9]*mat2->m_mat[6] + mat1->m_mat[13]*mat2->m_mat[7];
		mat[6] = mat1->m_mat[2]*mat2->m_mat[4] + mat1->m_mat[6]*mat2->m_mat[5] +mat1->m_mat[10]*mat2->m_mat[6] + mat1->m_mat[14]*mat2->m_mat[7];
		mat[7] = mat1->m_mat[3]*mat2->m_mat[4] + mat1->m_mat[7]*mat2->m_mat[5] +mat1->m_mat[11]*mat2->m_mat[6] + mat1->m_mat[15]*mat2->m_mat[7];
		mat[8] = mat1->m_mat[0]*mat2->m_mat[8] + mat1->m_mat[4]*mat2->m_mat[9] +mat1->m_mat[8]*mat2->m_mat[10] + mat1->m_mat[12]*mat2->m_mat[11];
		mat[9] = mat1->m_mat[1]*mat2->m_mat[8] + mat1->m_mat[5]*mat2->m_mat[9] +mat1->m_mat[9]*mat2->m_mat[10] + mat1->m_mat[13]*mat2->m_mat[11];
		mat[10] = mat1->m_mat[2]*mat2->m_mat[8] + mat1->m_mat[6]*mat2->m_mat[9] +mat1->m_mat[10]*mat2->m_mat[10] + mat1->m_mat[14]*mat2->m_mat[11];
		mat[11] = mat1->m_mat[3]*mat2->m_mat[8] + mat1->m_mat[7]*mat2->m_mat[9] +mat1->m_mat[11]*mat2->m_mat[10] + mat1->m_mat[15]*mat2->m_mat[11];
		mat[12] = mat1->m_mat[0]*mat2->m_mat[12] + mat1->m_mat[4]*mat2->m_mat[13] +mat1->m_mat[8]*mat2->m_mat[14] + mat1->m_mat[12]*mat2->m_mat[15];
		mat[13] = mat1->m_mat[1]*mat2->m_mat[12] + mat1->m_mat[5]*mat2->m_mat[13] +mat1->m_mat[9]*mat2->m_mat[14] + mat1->m_mat[13]*mat2->m_mat[15];
		mat[14] = mat1->m_mat[2]*mat2->m_mat[12] + mat1->m_mat[6]*mat2->m_mat[13] +mat1->m_mat[10]*mat2->m_mat[14] + mat1->m_mat[14]*mat2->m_mat[15];
		mat[15] = mat1->m_mat[3]*mat2->m_mat[12] + mat1->m_mat[7]*mat2->m_mat[13] +mat1->m_mat[11]*mat2->m_mat[14] + mat1->m_mat[15]*mat2->m_mat[15];

		memcpy(pOut->m_mat,mat,sizeof(float)*MATRIXSIZE);

		return pOut;
	}

	matrix4* MCopy( matrix4* pOut,matrix4* pIn )
	{
		if( pOut == pIn){
			return pOut;
		}

		memcpy(pOut->m_mat, pIn->m_mat, sizeof(float)*16);
		return pOut;
	}

	matrix4* MTranslatef( matrix4* pOut,float x,float y,float z )
	{
		MLoadIdentity(pOut);
		pOut->m_mat[12] = x;
		pOut->m_mat[13] = y;
		pOut->m_mat[14] = z;
		return pOut;
	}

	matrix4* MRotatef( matrix4* pOut,float degree,float x, float y ,float z )
	{
		MLoadIdentity(pOut);
		// normalize vector
		Vector3 vec(x,y,z);
		
		vec.normalize();
		x = vec.x;
		y = vec.y;
		z = vec.z;

		float rcos = cosf(degree);
		float rsin = sinf(degree);

		// rotate matrix
		pOut->m_mat[0] = rcos + (1 - rcos)*x*x;
		pOut->m_mat[1] = (1 - rcos)*y*x + rsin*z;
		pOut->m_mat[2] = (1 - rcos)*x*z - rsin*y;
		pOut->m_mat[3] = 0.0f;

		pOut->m_mat[4] = (1-rcos)*x*y - rsin*z;
		pOut->m_mat[5] = rcos + (1 - rcos)*y*y;
		pOut->m_mat[6] = (1 - rcos)*y*z + rsin*x;
		pOut->m_mat[7] = 0.0f;

		pOut->m_mat[8] = (1 - rcos)*x*z + rsin*y;
		pOut->m_mat[9] = (1 - rcos)*y*z - rsin*x;
		pOut->m_mat[10] = rcos + (1 - rcos)*z*z;
		pOut->m_mat[11] = 0.0f;

		pOut->m_mat[12] = pOut->m_mat[13] = pOut->m_mat[14] = 0.0f;
		pOut->m_mat[15] = 1.0f;
		return pOut;

	}

	matrix4* MScalef( matrix4* pOut,float x,float y,float z )
	{
		MLoadIdentity(pOut);
		pOut->m_mat[0] = x;
		pOut->m_mat[5] = y;
		pOut->m_mat[10] = z;

		return pOut;
	}

}