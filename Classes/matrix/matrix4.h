#ifndef _MATRIX4_H
#define _MATRIX4_H


namespace cxMatrix {


#define MATRIXSIZE 16
	/*
		4x4 matrix
					0	4	8	12
					1	5	9	13
		matrix =	2	6	10	14
					3	7	11	15

	*/	
	struct matrix4
	{
		float m_mat[MATRIXSIZE];
	};


	matrix4* MCreate(matrix4* pOut);
	matrix4* MLoadIdentity(matrix4* pOut);
	matrix4* MMult(matrix4* pOut,matrix4* mat1,matrix4* mat2);
	matrix4* MCopy(matrix4* pOut,matrix4* pIn);

	matrix4* MTranslatef(matrix4* pOut,float x,float y,float z);
	matrix4* MRotatef(matrix4* pOut,float degree,float x, float y ,float z);
	matrix4* MScalef(matrix4* pOut,float x,float y,float z);

}


#endif