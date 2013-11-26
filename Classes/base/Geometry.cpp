#include "Geometry.h"

namespace cxGeomety {


	Point::Point()
	{
		this->x = this->y = 0;
	}

	Point::Point( float x, float y )
	{
		this->x = x;this->y = y;
	}

	Point::~Point()
	{
		//TODO.
	}

	bool Point::operator==( const Point& pt )
	{
		return (x == pt.x) && (y == pt.y );
	}

	Point Point::operator+( const Point& pt )
	{
		return MakePoint( pt.x + x , pt.y + y);
	}

	Point Point::operator-( const Point& pt )
	{
		return MakePoint(x - pt.x ,y - pt.y);
	}

	Point Point::operator*( const float& scale )
	{
		return MakePoint( x * scale , y * scale);
	}

	Point Point::operator/( const float& scale )
	{
		return MakePoint( x / scale , y / scale);
	}

	Size::Size()
	{
		width = height = 0.0f;
	}

	Size::Size( float w,float h )
	{
		width = w;height = h;
	}

	Size::~Size()
	{

	}

	bool Size::operator==( const Size& sz )
	{
		return (width == sz.width) && (height == sz.height);
	}

	Size Size::operator+( const Size& sz )
	{
		return MakeSize(width + sz.width , height + sz.height);
	}

	Size Size::operator-( const Size& sz )
	{
		return MakeSize(width - sz.width , height - sz.height);
	}

	Size Size::operator*( const float& scale )
	{
		return MakeSize(width * scale , height * scale);
	}

	Size Size::operator/( const float& scale )
	{
		return MakeSize(width / scale , height / scale);
	}


	void gs_renderPoint( const Point& pt )
	{

	}


	Line::Line()
	{
		origin = destination = MakePoint(0,0);
	}

	Line::Line( const Point& origin , const Point& destination )
	{
		this->origin = origin;this->destination = destination;
	}

	Line::~Line()
	{

	}


	void gs_renderLine( const Line& rl )
	{

	}


	Triangle::Triangle()
	{
		vertex1 = vertex2 = vertex3 = MakePoint(0,0);
	}

	Triangle::Triangle( const Point& pt1,const Point& pt2,const Point& pt3 )
	{
		vertex1 = pt1; vertex2 = pt2 ; vertex3 = pt3;
	}

	Triangle::~Triangle()
	{

	}

	void gs_renderTriangle( const Triangle& triangle )
	{

	}





	Rect::Rect()
	{
		//point & size
	}

	Rect::Rect( const Point& pt , const Size& sz )
	{
		origin = pt;size = sz;
	}

	Rect::~Rect()
	{

	}

	bool Rect::intersertRect( const Rect& rt )
	{
		//
		return false;
	}

	void gs_renderRect( const Rect& rt )
	{

	}

}