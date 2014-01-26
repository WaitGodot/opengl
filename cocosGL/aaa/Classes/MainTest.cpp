#include "MainTest.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include "MacroConfig.h"
#include "file/Fileutils.h"
#include "shader/GLShaderMgr.h"
#include "shader/GLShaderProgram.h"

using namespace glShaderSpace;
using namespace std;

#include "base/Geometry.h"
#include "base/Color.h"
using namespace cxGeomety;

#include "matrix/MatrixPool.h"
#include "matrix/Vector3.h"
using namespace cxMatrix;

#include "base/timer.h"
//////////////////////////////////////////////////////////////////////////
// virtual test model
//���ؼ̳�
class C 
{
public:
	int c;
	virtual void vir_c()
	{

	}
};

class A :public virtual C
{
public:
	int a;
	virtual void vir_a()
	{

	}
};

class B : public virtual C
{
public:
	int b;
	virtual void vir_b()
	{

	}
};

class D :virtual public A,  public B
{
public:
	int d;
	virtual void vir_b()
	{

	}
};

void virMutilTest()
{
	A a1;B b1;C c1;D d1;
	d1.a = 1;d1.b = 2;d1.A::c = 3;d1.B::c = 4;d1.d =5;
	int szie_A = sizeof(a1);
	int szie_B = sizeof(b1);
	int szie_C = sizeof(c1);
	int szie_D = sizeof(d1);

}

//////////////////////////////////////////////////////////////////////////
// point
void pointTest()
{
	Point pt;
	pt = Point2f(1,1);
	Point pt1 = Point2f(2,2);

	Point result = pt + pt1;
	result = pt - pt1;
	result = pt + pt1;
	result = pt * 2.5;
	result = pt1/ 0.5;

	bool b = pt == pt1;
	pt1 = pt1 /2;
	b = pt == pt1;

	pt.x = 1;
	pt.y = 1;
	pt.z = 1;
	pt.render();
}

//////////////////////////////////////////////////////////////////////////
//macro
void macroTest()
{
	LOG_ERROR("log test!");
	LOG_ERROR("log test::::%d,%s",1,"3435");

	for (int i = 0 ; i < 10 ; i++)
	{
		BREAK_IF_LOG( i == 5," break of i == %d",i);
	}

	CHECK_GL_ERROR();
}

//////////////////////////////////////////////////////////////////////////
//file
void fileTest()
{
	unsigned long length = 0;
	unsigned char* data = gsShareFileUtils()->getFileData( gsShareFileUtils()->getFullPath("test.txt").c_str()
		,"r",length);
	data[8] = '\0';
	DELETE_ARRAY_FAFE(data);
	const char* path = gsShareFileUtils()->getFullPathNeedRelease("test/test.txt");
	data = gsShareFileUtils()->getFileData("test/test.txt","r",length);
	DELETE_ARRAY_FAFE(data);
	DELETE_ARRAY_FAFE(path);
}

//////////////////////////////////////////////////////////////////////////
// shader
void glShaderTest()
{
	GLShaderProgram* program = shareGLShaderManager()->getByKey(_Postion_Key);
}

//////////////////////////////////////////////////////////////////////////
// geometry 
void geometryTest()
{
	drawColor(0.5f,0.0f,0.0f,1.0f);
	Point2f(0.2,0.3).render();	
	drawColor(1.0f,1.0f,0.0f,1.0f);
	Point2f(0.5,0.1).render();
	drawColor(0.5f,0.5f,0.5f,1.0f);

	sg_renderLine(line2P(Point2f(-4,0),Point2f(4,0)));
	sg_renderLine(line2P(Point2f(0,-8),Point2f(0,8)));

	drawColor(0.0f,0.0f,0.0f,1.0f);
	sg_randerStripLine(5,Point2f(-1,0),Point2f(0,1),Point2f(1,0),Point2f(0,-1),Point2f(-1,0));
	drawColor(0.5f,0.5f,0.2f,1.0f);
	sg_randerLoopLine(6,Point2f(-1,0),Point2f(-sin(30*PI/180),sin(60*PI/180)),
		Point2f(sin(30*PI/180),sin(60*PI/180)),Point2f(1,0),
		Point2f(sin(30*PI/180),-sin(60*PI/180)),Point2f(-sin(30*PI/180),-sin(60*PI/180)));

	sg_renderTriangle(triangle3P(Point2f(0,0),Point2f(1,0),Point2f(sin(30*PI/180),sin(60*PI/180))));
	drawColor(1,1,0,1);
	sg_randerTrianglStrip(5,Point2f(0,0),Point2f(0,-0.2),Point2f(-0.2,0),Point2f(-0.2,-0.2),Point2f(-0.4,0));
	drawColor(1,0,1,1);
	sg_randerTrianglFan(6,Point2f(0,0),Point2f(0.5,0),Point2f(sin(45*PER_DEGREE)*0.5,sin(45*PER_DEGREE)*0.5),
		Point2f(0,0.5),Point2f(-sin(45*PER_DEGREE)*0.5,sin(45*PER_DEGREE)*0.5),Point2f(-0.5,0) );

	sg_renderRect(rect2P( Point2f(0.2,-0.2),Point2f(-0.4,-0.4)));
	drawColor(0,1,1,1);
	sg_renderRect(rect2P( Point2f(0.25,-0.2),Point2f(0.4,-0.4)) ,true);
}

//////////////////////////////////////////////////////////////////////////
// vector3
void vector3Test()
{
	Vector3 vec(0,0,2);
	Vector3 vec1(0,1,0);
	Vector3 pOut;
	Vector3::CrossVector3(&pOut,&vec,&vec1);
}

//////////////////////////////////////////////////////////////////////////
// cube
void cubeTest()
{
	static float s_d = 0;
	cxGLPushMatrix();
	{
		//cxGLTranslatef(1,0,0);
 		//cxGLScalef(0.4,0.5,0.6);
		//cxGLRotatef(s_d,0,0,1);
		drawCube(2);
	}
	cxGLPopMatrix();
	s_d+=0.1;
}

//////////////////////////////////////////////////////////////////////////
// light
void lightInit()
{

}

void lightTest()
{
	cxGLPushMatrix();
	{
// 		cxGLTranslatef(-3,0,0);
// 		glutSolidSphere(1,20,20);
	}
	cxGLPopMatrix();

}

timer sg_timer;
void lightningTest()
{

	Point2f(0,0).render();

	cxGLPushMatrix();
	{
		GLShaderProgram* program = shareGLShaderManager()->getByKey(_Lightning_key);
		program->use();

		program->updateMVPMatrix();

		GLint l_position = program->getVertexAttLoction(_Vertex_Position);
		GLint l_resolution = glGetUniformLocation(program->getProgram(),"u_resolution");
		GLint l_globalTime = glGetUniformLocation(program->getProgram(),"u_globalTime");

		GLfloat vec3[] = {0,0,0};

		glEnableVertexAttribArray( l_position );
		glVertexAttribPointer(l_position,3,GL_FLOAT,GL_FALSE,0,vec3);

// 
// 		glUniform3f(l_resolution,1,1,1);
// 		float dt = sg_timer.elapsed();
// 		glUniform1f(l_globalTime,dt);

		glDrawArrays(GL_POINTS,0,1);
	}
	cxGLPopMatrix();
}
