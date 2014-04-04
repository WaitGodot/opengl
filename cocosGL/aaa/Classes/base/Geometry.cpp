#include "Geometry.h"
#include "shader/GLShaderProgram.h"
#include "shader/GLShaderMgr.h"
#include "MacroConfig.h"
#include "Color.h"
#include "matrix/Matrix4x4.h"
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
		GLShaderProgram* program = shareGLShaderManager()->getByKey(_Postion_Key);
		program->use();
	
		GLint l_position = program->getVertexAttLoction(_Vertex_Position);
		GLint l_color = program->getVertexUniformLoction(U_COLOR);
		GLint l_pointsize = program->getVertexUniformLoction(U_POINTSIZE);
		
		glEnable(GL_PROGRAM_POINT_SIZE);

		//glUniform1f(l_pointsize,sg_pointSize);
		glUniform4fv(l_color,1,sg_color);
		program->updateMVPMatrix();

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
		
		pShader->updateMVPMatrix();
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);
		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_FALSE,0,&rl);
	
		glDrawArrays(GL_LINES,0,2);
		CHECK_GL_ERROR();
	

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
		//glFrontFace(GL_CW);//FORNT default : GL_CW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();
		pShader->updateMVPMatrix();

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
		//glFrontFace(GL_CW);//FORNT default : GL_CW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_Postion_Key);
		pShader->use();
		pShader->updateMVPMatrix();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);

		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,vertex);

		glDrawArrays(GL_POLYGON,0,4);
	}

	void sg_randerRect( Point* vertex,Vector3* vecs, int numbOfPoint,bool isFill /*= false*/ )
	{
		glPolygonMode(GL_FRONT_AND_BACK, isFill ? GL_FILL : GL_LINE);
		//glFrontFace(GL_CW);//FORNT default : GL_CCW,clock wise
		GLShaderProgram* pShader = shareGLShaderManager()->getByKey(_AdsLight_key);
		pShader->use();
		
		pShader->updateMVMatrix();
		pShader->updateMVPMatrix();
		GLLight* pLight = pShader->getGlLight();
		//pLight->getLightAtt()->m_ambient = Vector4(1,1,1,1);
 		pLight->getLightAtt()->m_position = Vector4(0,0,5,1);
// 		pLight->getLightAtt()->m_diffuse = Vector4(0.5,0.5,0.5,1);
// 		pLight->getLightAtt()->m_specular = Vector4(0,0.5,0.5,1);
// 		pLight->getLightAtt()->m_linear_attenuation = 1.0;
// 		//pLight->getLightAtt()->m_quadratic_attenuation = 2.0f;
 		pLight->getLightAtt()->setSpotCutoff(20);
		pLight->getLightAtt()->m_spot_exponent = 1.0f;
// 		pLight->getLightAtt()->m_spot_dirction = Vector3(0,0,-1);

		pLight->getLightMatrialAtt()->m_m_emission = Vector4(0,0,0,1);
		pLight->getLightMatrialAtt()->m_m_ambient = Vector4(0,0,0,1);
		pLight->getLightMatrialAtt()->m_m_diffuse = Vector4(0.5,0,0,1);
 		pLight->getLightMatrialAtt()->m_m_shininess = 66;
 		pLight->getLightMatrialAtt()->m_m_specular = Vector4(0,1,0,1);
		pShader->updateAllLight();

		GLint l_postion = pShader->getVertexAttLoction(_Vertex_Position);
		GLint l_u_color = pShader->getVertexUniformLoction(U_COLOR);
		GLint l_normal = pShader->getVertexAttLoction(_Vertex_Normal);

		glUniform4fv(l_u_color,1,sg_color);
		glEnableVertexAttribArray(l_postion);
		glVertexAttribPointer(l_postion ,3,GL_FLOAT,GL_TRUE,0,vertex);

		glEnableVertexAttribArray(l_normal);
		glVertexAttribPointer(l_normal, 3, GL_FLOAT,GL_TRUE,0,vecs);

		
		for (int i = 0 ; i < 24 ; i+=4)
		{
			glDrawArrays(GL_POLYGON,i,4);
		}
		
	}

	Vector3 createNormal(const Point& p1,const Point& p2 ,const Point& p3)
	{
		Point pp1 = p2 -p1;
		Point pp2 = p3 - p1;
		Vector3 v1(pp1.x,pp1.y,pp1.z);
		Vector3 v2(pp2.x, pp2.y,pp2.z);
		Vector3 pOut;

		Vector3::CrossVector3(&pOut,&v1,&v2);
		return pOut;

	}

	void drawCube( float s )
	{
		float hs = s/2;
		Point vertex[24];
		Vector3 vec3[24];
		//up
		vertex[0] = Point3f(-hs,hs,hs);
		vertex[1] = Point3f(hs,hs,hs);
		vertex[2] = Point3f(hs,hs,-hs);
		vertex[3] = Point3f(-hs,hs,-hs);
		vec3[0] = createNormal( vertex[0],vertex[1],vertex[3]);
		vec3[1] = createNormal( vertex[1],vertex[2],vertex[0]);
		vec3[2] = createNormal( vertex[2],vertex[3],vertex[1]);
		vec3[3] = createNormal( vertex[3],vertex[0],vertex[2]);

		//down
		vertex[4] = Point3f(-hs,-hs,hs);
		vertex[5] = Point3f(-hs,-hs,-hs);
		vertex[6] = Point3f(hs,-hs,-hs);
		vertex[7] = Point3f(hs,-hs,hs);
		vec3[4] = createNormal( vertex[4],vertex[5],vertex[7]);
		vec3[5] = createNormal( vertex[5],vertex[6],vertex[4]);
		vec3[6] = createNormal( vertex[6],vertex[7],vertex[5]);
		vec3[7] = createNormal( vertex[7],vertex[4],vertex[6]);
		
		//left
		vertex[8] = Point3f(-hs,-hs,hs);
		vertex[9] = Point3f(-hs,hs,hs);
		vertex[10] = Point3f(-hs,hs,-hs);
		vertex[11] = Point3f(-hs,-hs,-hs);
		vec3[8] = createNormal( vertex[8],vertex[9],vertex[11]);
		vec3[9] = createNormal( vertex[9],vertex[10],vertex[8]);
		vec3[10] = createNormal( vertex[10],vertex[11],vertex[9]);
		vec3[11] = createNormal( vertex[11],vertex[8],vertex[10]);

		//right
		vertex[12] = Point3f(hs,-hs,hs);
		vertex[13] = Point3f(hs,-hs,-hs);
		vertex[14] = Point3f(hs,hs,-hs);
		vertex[15] = Point3f(hs,hs,hs);
		vec3[12] = createNormal( vertex[12],vertex[13],vertex[15]);
		vec3[13] = createNormal( vertex[13],vertex[14],vertex[12]);
		vec3[14] = createNormal( vertex[14],vertex[15],vertex[13]);
		vec3[15] = createNormal( vertex[15],vertex[12],vertex[14]);

		//front
		vertex[16] = Point3f(-hs,-hs,hs);
		vertex[17] = Point3f(hs,-hs,hs);
		vertex[18] = Point3f(hs,hs,hs);
		vertex[19] = Point3f(-hs,hs,hs);
		vec3[16] = createNormal( vertex[16],vertex[17],vertex[19]);
		vec3[17] = createNormal( vertex[17],vertex[18],vertex[16]);
		vec3[18] = createNormal( vertex[18],vertex[19],vertex[17]);
		vec3[19] = createNormal( vertex[19],vertex[16],vertex[18]);
		//back
		vertex[20] = Point3f(-hs,-hs,-hs);
		vertex[21] = Point3f(-hs,hs,-hs);
		vertex[22] = Point3f(hs,hs,-hs);
		vertex[23] = Point3f(hs,-hs,-hs);
		vec3[20] = createNormal( vertex[20],vertex[21],vertex[23]);
		vec3[21] = createNormal( vertex[21],vertex[22],vertex[20]);
		vec3[22] = createNormal( vertex[22],vertex[23],vertex[21]);
		vec3[23] = createNormal( vertex[23],vertex[20],vertex[22]);

		sg_randerRect(vertex,vec3,24,true);
	}

	void drawSphere( float rudis,int slices,int stacks )
	{

	}







}