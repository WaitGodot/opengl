#ifndef _VECTOR4_H
#define _VECTOR4_H


namespace cxMatrix
{

	class Vector4
	{
	public:
		float x,y,z,w;
	public:
		Vector4();
		Vector4(float x,float y,float z,float w);
		~Vector4();

		void normalize();
		float length();
		float dot(Vector4* vec);

		// static
		static Vector4* NormalizeVector4(Vector4* pOut);
		static float DotVector4(Vector4* vec1,Vector4* vec2);
		
		//operator
		Vector4 operator+ (const Vector4& vec);
		Vector4 operator- (const Vector4& vec);
		void	operator= (const Vector4& vec);
	};

}



#endif