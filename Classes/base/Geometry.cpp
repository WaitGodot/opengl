#include "Geometry.h"
#include "shader/GLShaderProgram.h"
#include "shader/GLShaderManager.h"
#include "_MacroConfig.h"
#include "Color.h"

using namespace glShaderSpace;

namespace cxGeomety {


	static Color sg_color = color3f(1.0f,1.0f,1.0f) ;

	void drawColor( Color& color )
	{
		sg_color = color;
	}


	Point::Point()
	{
		this->x = this->y = this->z = 0;
	}

	Point::Point( float x, float y ,float z)
	{
		this->x = x;this->y = y; this->z = z;
	}

	Point::~Point()
	{
		//TODO.
	}

	bool Point::operator==( const Point& pt )
	{
		return (x == pt.x) && (y == pt.y ) && ( z == pt.z );
	}

	Point Point::operator+( const Point& pt )
	{
		return Point3f( pt.x + x , pt.y + y , pt.z + z);
	}

	Point Point::operator-( const Point& pt )
	{
		return Point3f(x - pt.x ,y - pt.y , z - pt.z);
	}

	Point Point::operator*( const float& scale )
	{
		return Point3f( x * scale , y * scale , z * scale);
	}

	Point Point::operator/( const float& scale )
	{
		return Point3f( x / scale , y / scale , z / scale);
	}

	void Point::render()
	{
		GLShaderProgram* progam = shareGLShaderManager()->getByKey(_Postion_Key);
		progam->use();
	
		GLint l_position = progam->getVertexAttLoction(_Vertex_Position);
		GLint l_color = progam->getVertexAttLoction(_Vertex_Color);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnableVertexAttribArray( l_position );
		glVertexAttribPointer(l_position,3,GL_FLOAT,GL_FALSE,0,this);
		glEnableVertexAttribArray( l_color );
		glVertexAttribPointer(l_color,4,GL_UNSIGNED_BYTE,GL_FALSE,0,&sg_color);
		glDrawArrays(GL_POINTS,0,1);
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




	Line::Line()
	{
		origin = destination = Point2f(0,0);
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
		vertex1 = vertex2 = vertex3 = Point2f(0,0);
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