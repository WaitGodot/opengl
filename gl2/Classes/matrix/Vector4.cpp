#include "Vector4.h"
#include <math.h>
#include "MacroConfig.h"

namespace cxMatrix
{


	Vector4::Vector4():
		x(0),y(0),z(0),w(0)
	{

	}

	Vector4::Vector4(float x,float y,float z,float w):
		x(x),y(y),z(z),w(w)
	{

	}

	Vector4::~Vector4()
	{
	
	}

	void Vector4::normalize()
	{
		NormalizeVector4(this);
	}

	float Vector4::length()
	{
		return sqrtf( (x*x + y*y + z*z + w*w));
	}

	float Vector4::dot( Vector4* vec )
	{
		return x * vec->x + y * vec->y + z * vec->z + w * vec->w ;
	}

	Vector4* Vector4::NormalizeVector4( Vector4* pOut )
	{
		float l = pOut->length();
		if (l == 1 ||  l < MATH_TOLERANCE)
		{
			return  pOut;
		}

		float s = 1.0f /  l;

		pOut->x *= s;
		pOut->y *= s;
		pOut->z *= s;

		return pOut;
	}

	float Vector4::DotVector4( Vector4* vec1,Vector4* vec2 )
	{
		return vec1->dot(vec2);
	}

	Vector4 Vector4::operator+( const Vector4& vec )
	{
		return Vector4(x + vec.x , y + vec.y , z + vec.z , w + vec.w);
	}

	Vector4 Vector4::operator-( const Vector4& vec )
	{
		return Vector4(x - vec.x , y - vec.y , z - vec.z , w - vec.w);
	}

	void Vector4::operator=( const Vector4& vec )
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}



}