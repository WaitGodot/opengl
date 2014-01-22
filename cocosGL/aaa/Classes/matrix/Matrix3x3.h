#ifndef _MATRIX_3X3_H
#define _MATRIX_3X3_H


namespace cxMatrix
{

	

	#define MATRIX_3X3_SIZE 9
	/*
		3x3 matrix
					0	3	6
		matrix =	1	4	7
					2	5	8
		

	*/	
	struct Matrix3x3
	{
		float mat[MATRIX_3X3_SIZE];
	};


	Matrix3x3* MCreate3x3(Matrix3x3* pOut);
	Matrix3x3* MLoadIdentity3x3(Matrix3x3* pOut);
	Matrix3x3* MMult3x3(Matrix3x3* pOut,Matrix3x3* mat1,Matrix3x3* mat2);
	Matrix3x3* MCopy3x3(Matrix3x3* pOut,Matrix3x3* pIn);

}


#endif