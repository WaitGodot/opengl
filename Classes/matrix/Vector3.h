#ifndef _VECTOR3_H
#define _VECTOR3_H



namespace cxMatrix
{

	//vector.

	class Vector3
	{
	public:
		float x,y,z;

	public:
		Vector3();
		Vector3(float x,float y,float z);
		~Vector3();

		void normalize();
		float length();
		float dot(Vector3* vec);
		Vector3* cross(Vector3* pOut,Vector3* vec1);
		

		// static
		static Vector3* NormalizeVector3(Vector3* pOut);
		static Vector3* CrossVector3(Vector3* pOut,Vector3* vec1,Vector3* vec2);// vec1X vec2;
		static float DotVector3(Vector3* vec1,Vector3* vec2);
		
		static Vector3* Subtract(Vector3* pOut,Vector3* vec1,Vector3* vec2);
	};


}

#endif