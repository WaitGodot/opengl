#include "Vector3.h"
#include <math.h>

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f


namespace cxMatrix
{


	Vector3::Vector3()
	{
		x = y = z = 0;
	}

	Vector3::Vector3(float x,float y,float z)
	{
		this->x = x;this->y = y;this->z = z;
	}

	Vector3::~Vector3()
	{

	}

	void Vector3::normalize()
	{
		NormalizeVector3(this);
	}

	float Vector3::length()
	{
		return sqrtf( (x*x + y*y + z*z));
	}

	Vector3* Vector3::cross( Vector3* pOut,Vector3* vec1 )
	{
		pOut->x = y * vec1->z - z * vec1->y;
		pOut->y = z * vec1->x - x * vec1->z;
		pOut->z = x * vec1->y - y * vec1->x;

		return pOut;
	}

	float Vector3::dot( Vector3* vec )
	{
		return x * vec->x + y * vec->y + z * vec->z;
	}

	Vector3* Vector3::NormalizeVector3( Vector3* pOut )
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

	Vector3* Vector3::CrossVector3( Vector3* pOut,Vector3* vec1,Vector3* vec2 )
	{
		return vec1->cross(pOut,vec2);
	}

	float Vector3::DotVector3( Vector3* vec1,Vector3* vec2 )
	{
		return vec1->dot(vec2);
	}

	Vector3* Vector3::Subtract( Vector3* pOut,Vector3* vec1,Vector3* vec2 )
	{
		pOut->x = vec1->x - vec2->x;
		pOut->y = vec1->y - vec2->y;
		pOut->z = vec1->z - vec2->z;

		return pOut;
	}


}