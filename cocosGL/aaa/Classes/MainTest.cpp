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

#include "timer/timer.h"
#include "texture/Image.h"
#include "texture/Sprite.h"
#include "texture/Texture.h"

//////////////////////////////////////////////////////////////////////////
// virtual test model
//∂‡÷ÿºÃ≥–
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
	DELETE_ARRAY_SAFE(data);
	const char* path = gsShareFileUtils()->getFullPathNeedRelease("test/test.txt");
	data = gsShareFileUtils()->getFileData("test/test.txt","r",length);
	DELETE_ARRAY_SAFE(data);
	DELETE_ARRAY_SAFE(path);
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

//////////////////////////////////////////////////////////////////////////
// lightning

static timer sg_timer;
static Point sg_start = Point2f(-2,0);
static Point sg_end = Point2f(2,0);

static int count = 10;
static float cuoff = cosf(DEGREE(30));

void renderOneLightning(Point curentpoint ,Point prepoint)
{
	float x = curentpoint.x + ( sg_end.x - sg_start.x)/count ;
	if( curentpoint.x >= sg_end.x || x > sg_end.x)
	{
		return ;
	}
	float y = 1 * MATH_RANDOM_MINUS1_1();

	Point nextPoint = Point2f(x,y);
	Vector3 vec1( curentpoint.x - sg_start.x , curentpoint.y - sg_start.y ,curentpoint.z - prepoint.z);
	Vector3 vec2( nextPoint.x - curentpoint.x , nextPoint.y - curentpoint.y ,nextPoint.z - curentpoint.z);
	vec1.normalize();
	vec2.normalize();

	float cdt = vec1.dot(&vec2);
	cdt = cdt > 0 ? cdt : 0;

	if ( cdt > cuoff)
	{
		sg_renderLine(line2P(curentpoint,nextPoint) );
		renderOneLightning(nextPoint,curentpoint);
	}else
	{
		renderOneLightning(curentpoint,prepoint);
	}
	

	
}



void lightningTest()
{
	cxGLPushMatrix();
	{
		renderOneLightning(sg_start,Point2f(-3,0));

	}
	cxGLPopMatrix();
}

//////////////////////////////////////////////////////////////////////////
// texture
void imageTest()
{

	Image* p = Image::create("test.png");
}

void spriteTest()
{
	CHECK_GL_ERROR();
	static Image* p = Image::create("test.png");
	static Texture* ptx = Texture::create(p);
	static Sprite* pSp = Sprite::create(ptx);
	pSp->draw();
}

//////////////////////////////////////////////////////////////////////////
//ffmpeg : ffmpegTest.cpp
//////////////////////////////////////////////////////////////////////////