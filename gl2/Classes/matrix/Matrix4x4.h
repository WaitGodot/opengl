#ifndef _MATRIX4_H
#define _MATRIX4_H


namespace cxMatrix {


#define MATRIX_4X4_SIZE 16
	/*
		4x4 matrix
					0	4	8	12
					1	5	9	13
		matrix =	2	6	10	14
					3	7	11	15

	*/	
	struct Matrix3x3;

	struct Matrix4x4
	{
		float mat[MATRIX_4X4_SIZE];
	};


	Matrix4x4* MCreate4x4(Matrix4x4* pOut);
	Matrix4x4* MLoadIdentity4x4(Matrix4x4* pOut);
	Matrix4x4* MMult4x4(Matrix4x4* pOut,Matrix4x4* mat1,Matrix4x4* mat2);
	Matrix4x4* MCopy4x4(Matrix4x4* pOut,Matrix4x4* pIn);

	Matrix4x4* MTranslatef4x4(Matrix4x4* pOut,float x,float y,float z);
	Matrix4x4* MRotatef4x4(Matrix4x4* pOut,float degree,float x, float y ,float z);
	Matrix4x4* MScalef4x4(Matrix4x4* pOut,float x,float y,float z);

	Matrix3x3* MMat4ExtractRotation(Matrix3x3* pOut,Matrix4x4* pIn);
	Matrix4x4* MMat3TransformMat4(Matrix4x4* pOut,Matrix3x3* pIn);
}


#endif