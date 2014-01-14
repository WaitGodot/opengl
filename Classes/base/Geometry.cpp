#include "Geometry.h"
#include "shader/GLShaderProgram.h"
#include "shader/GLShaderManager.h"
#include "_MacroConfig.h"
#include "Color.h"
#include "matrix/matrix4.h"
#include "matrix/MatrixPool.h"

#include <stdarg.h>
#include <iostream>
using namespace glShaderSpace;
using namespace cxMatrix;

namespace cxGeomety {


	static float sg_color[4] = {1.0f,1.0f,1.0f,1.0f} ;
	static float sg_pointSize = 1.0f;


	void drawColor( float r,float g,float b,float a )
	{
		sg_color[0] = r;sg_color[1] = g;sg_color[2] = b;sg_color[3] = a;
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
		GLint l_color = progam->getVertexUniformLoction(U_COLOR);
		GLint l_pointsize = progam->getVertexUniformLoction(U_POINTSIZE);
		GLint l_matrix = progam->getVertexUniformLoction(U_MODELVIEWMATRIX);

		cxGLPushMatrix();
			cxGLLoadentity();
			cxGLTranslatef(0.5,0,0);
			cxGLUniformMatrix4f(l_matrix);
		cxGLPopMatrix();
		glEnable(GL_PROGRAM_POINT_SIZE);
		sg_pointSize = 5;
		glUniform1f(l_pointsize,sg_pointSize);
		glUniform4fv(l_color,1,sg_color);
		//glUniformMatrix4fv(l_matrix,1,GL_FALSE,mat4->m_mat);

		//GLfloat vectex[3] = {10.0f,10.0f,0/500.0f};
		glEnableVertexAttribArray( l_position );
		glVertexAttribPointer(l_position,3,GL_FLOAT,GL_FALSE,0,PVCLASSDATA(this));


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
		return size2f(width + sz.width , height + sz.height);
	}

	Size Size::operator-( const Size& sz )
	{
		return size2f(width - sz.width , height - sz.height);
	}

	Size Size::operator*( const float& scale )
	{
		return size2f(width * scale , height * scale);
	}

	Size Size::operator/( const float& scale )
	{
		return size2f(width / scale , height / scale);
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


	void sg_renderLine( const Line& rl )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		//GLint l_matrix = pShader->getVertexUniformLoction(U_MODELVIEWMATRIX);
		static float radius = 0;
		radius += 0.01;
		cxGLPushMatrix();
			//cxGLLoadentity();
			//cxGLTranslatef(0,0,-1);
			//cxGLScalef(radius,radius,1);
			//cxGLRotatef(radius,1,0,0);
		
			pShader->setMVPMatrix();

			glUniform4fv(l_u_color,1,sg_color);
			glEnableVertexAttribArray(l_postion);
			glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_FALSE,0,&rl);
	
			glDrawArrays(GL_LINES,0,2);
			CHECK_GL_ERROR();
		cxGLPopMatrix();

	}

	void sg_randerStripLine( int number,... )
	{
		va_list args;
		va_start(args,number);
		Point* arr = new Point[number];
		for(int i = 0 ; i < number ; i++) 
		{
			 arr[i]= va_arg(args, Point);
		}
		va_end(args);
		sg_randerStripLine(number,arr);
		delete [] arr;
		CHECK_GL_ERROR();
	}

	void sg_randerStripLine( int number,Point* arr )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);
		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_FALSE,0,arr);

		glDrawArrays(GL_LINE_STRIP,0,number);
	}

	void sg_randerLoopLine( int number,... )
	{
		va_list args;
		va_start(args,number);
		Point* arr = new Point[number];
		for(int i = 0 ; i < number ; i++) 
		{
			arr[i]= va_arg(args, Point);
		}
		va_end(args);
		sg_randerLoopLine(number,arr);
		delete [] arr;
		CHECK_GL_ERROR();
	}

	void sg_randerLoopLine( int number,Point* arr )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);
		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,arr);

		glDrawArrays(GL_LINE_LOOP,0,number);
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

	void sg_renderTriangle( const Triangle& triangle )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		//the counter clock wise is the front
		//glPolygonMode(GL_FRONT,GL_FILL);
		//glPolygonMode(GL_BACK,GL_LINE);

		//glFrontFace(GL_CW);//counter clock wise

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);
		
		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,&triangle);

		glDrawArrays(GL_TRIANGLES,0,3);
		CHECK_GL_ERROR();
	}

	void sg_randerTrianglStrip( int number,... )
	{
		va_list args;
		va_start(args,number);
		Point* arr = new Point[number];
		for(int i = 0 ; i < number ; i++) 
		{
			arr[i]= va_arg(args, Point);
		}
		va_end(args);

		sg_randerTrianglStrip(number,arr);
		delete [] arr;
	}

	void sg_randerTrianglStrip( int number,Point* arr )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,arr);

		glDrawArrays(GL_TRIANGLE_STRIP,0,number);
	}

	void sg_randerTrianglFan( int number,... )
	{
		va_list args;
		va_start(args,number);
		Point* arr = new Point[number];
		for(int i = 0 ; i < number ; i++) 
		{
			arr[i]= va_arg(args, Point);
		}
		va_end(args);
		sg_randerTrianglFan(number,arr);
		delete [] arr;
	}

	void sg_randerTrianglFan( int number,Point* arr )
	{
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,arr);

		glDrawArrays(GL_TRIANGLE_FAN,0,number);
	}

	Rect::Rect()
	{
		//point & size
	}

	Rect::Rect( const Point& pt , const Point& dt )
	{
		origin = pt;destination = dt;
	}

	Rect::~Rect()
	{

	}

	bool Rect::intersertRect( const Rect& rt )
	{
		//
		return false;
	}

	void sg_renderRect( const Rect& rt ,bool isFill)
	{
		Point vectex[4] = {
			rt.origin,
			Point3f(rt.origin.x ,rt.destination.y,rt.destination.z),
			rt.destination,
			Point3f(rt.destination.x,rt.origin.y ,rt.origin.z),
		};

		glPolygonMode(GL_FRONT, isFill ? GL_FILL : GL_LINE);
		glFrontFace(GL_CW);//FORNT default : GL_CW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();
		pShader->setMVPMatrix();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,vectex);

		glDrawArrays(GL_POLYGON,0,4);
	}

	void sg_randerRect( Point* vertex, bool isFill /*= false*/ )
	{
		glPolygonMode(GL_FRONT_AND_BACK, isFill ? GL_FILL : GL_LINE);
		glFrontFace(GL_CW);//FORNT default : GL_CW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();
		pShader->setMVPMatrix();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,vertex);

		glDrawArrays(GL_POLYGON,0,4);
	}

	void sg_randerRect( Point* vertex, int numbOfPoint,bool isFill /*= false*/ )
	{
		glPolygonMode(GL_FRONT_AND_BACK, isFill ? GL_FILL : GL_LINE);
		glFrontFace(GL_CW);//FORNT default : GL_CW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();
		pShader->setMVPMatrix();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,vertex);
		for (int i = 0; i < numbOfPoint ; i +=4)
		{
			glDrawArrays(GL_POLYGON,i,4);
		}
		//glDrawArrays(GL_POLYGON,0,4);
	}

// 	void drawCube( float s )
// 	{
// 		float hs = s/2;
// 		Point vertex[4];
// 		//up
// 		vertex[0] = Point3f(-hs,hs,hs);
// 		vertex[1] = Point3f(-hs,hs,-hs);
// 		vertex[2] = Point3f(hs,hs,-hs);
// 		vertex[3] = Point3f(hs,hs,hs);
// 		sg_randerRect(vertex);
// 		//down
// 		vertex[0] = Point3f(-hs,-hs,hs);
// 		vertex[1] = Point3f(-hs,-hs,-hs);
// 		vertex[2] = Point3f(hs,-hs,-hs);
// 		vertex[3] = Point3f(hs,-hs,hs);
// 		sg_randerRect(vertex);
// 		//left
// 		vertex[0] = Point3f(-hs,-hs,hs);
// 		vertex[1] = Point3f(-hs,-hs,-hs);
// 		vertex[2] = Point3f(-hs,hs,-hs);
// 		vertex[3] = Point3f(-hs,hs,hs);
// 		sg_randerRect(vertex);
// 		//right
// 		vertex[0] = Point3f(hs,-hs,hs);
// 		vertex[1] = Point3f(hs,-hs,-hs);
// 		vertex[2] = Point3f(hs,hs,-hs);
// 		vertex[3] = Point3f(hs,hs,hs);
// 		sg_randerRect(vertex);
// 		//front
// 		vertex[0] = Point3f(-hs,-hs,hs);
// 		vertex[1] = Point3f(-hs,hs,hs);
// 		vertex[2] = Point3f(hs,hs,hs);
// 		vertex[3] = Point3f(hs,-hs,hs);
// 		sg_randerRect(vertex);
// 		//back
// 		vertex[0] = Point3f(-hs,-hs,-hs);
// 		vertex[1] = Point3f(-hs,hs,-hs);
// 		vertex[2] = Point3f(hs,hs,-hs);
// 		vertex[3] = Point3f(hs,-hs,-hs);
// 		sg_randerRect(vertex);
// 	}

	void drawCube( float s )
	{
		float hs = s/2;
		Point vertex[24];
		//up
		vertex[0] = Point3f(-hs,hs,hs);
		vertex[1] = Point3f(-hs,hs,-hs);
		vertex[2] = Point3f(hs,hs,-hs);
		vertex[3] = Point3f(hs,hs,hs);
		
		//down
		vertex[4] = Point3f(-hs,-hs,hs);
		vertex[5] = Point3f(-hs,-hs,-hs);
		vertex[6] = Point3f(hs,-hs,-hs);
		vertex[7] = Point3f(hs,-hs,hs);
		
		//left
		vertex[8] = Point3f(-hs,-hs,hs);
		vertex[9] = Point3f(-hs,-hs,-hs);
		vertex[10] = Point3f(-hs,hs,-hs);
		vertex[11] = Point3f(-hs,hs,hs);
		
		//right
		vertex[12] = Point3f(hs,-hs,hs);
		vertex[13] = Point3f(hs,-hs,-hs);
		vertex[14] = Point3f(hs,hs,-hs);
		vertex[15] = Point3f(hs,hs,hs);
		
		//front
		vertex[16] = Point3f(-hs,-hs,hs);
		vertex[17] = Point3f(-hs,hs,hs);
		vertex[18] = Point3f(hs,hs,hs);
		vertex[19] = Point3f(hs,-hs,hs);
		
		//back
		vertex[20] = Point3f(-hs,-hs,-hs);
		vertex[21] = Point3f(-hs,hs,-hs);
		vertex[22] = Point3f(hs,hs,-hs);
		vertex[23] = Point3f(hs,-hs,-hs);
		sg_randerRect(vertex,24);
	}
	





}