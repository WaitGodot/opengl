#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include "_MacroConfig.h"
#include "file/Fileutils.h"
#include "shader/GLShaderManager.h"
#include "shader/GLShaderProgram.h"

using namespace glShaderSpace;
using namespace std;

#include "base/Geometry.h"
#include "base/Color.h"
using namespace cxGeomety;


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
}

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

void fielTest()
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

void glShaderTest()
{
	GLShaderProgram* program = shareGLShaderManager()->getByKey(_Postion_Key);
}

void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}



void geometryTest()
{
	drawColor(0.5f,0.0f,0.0f,1.0f);
	Point2f(0.2,0.3).render();	
	drawColor(1.0f,1.0f,0.0f,1.0f);
	Point2f(0.5,0.1).render();
	drawColor(0.5f,0.5f,0.5f,1.0f);
	sg_renderLine(line2P(Point2f(-1,0),Point2f(1,0)));
	sg_renderLine(line2P(Point2f(0,-1),Point2f(0,1)));

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

void display()
{
	glClearColor(0,0.4,0.6,1);
	glClear(GL_COLOR_BUFFER_BIT);  
	
	geometryTest();


// 
// 	GLShaderProgram* progam = shareGLShaderManager()->getByKey(_Postion_Key);
// 	progam->use();
// 
// 	GLint location = progam->getVertexAttLoction(_Vertex_Position);
// 
// 	GLfloat vertices[] = {
// 		0.0f,  0.5f, 0.0f, 
// 		-0.5f, -0.5f, 0.0f,
// 		0.5f,  -0.5f, 0.0f };
// 
// 		glEnableVertexAttribArray(location);
// 		CHECK_GL_ERROR();
// 	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, vertices );
// 	CHECK_GL_ERROR();
// 	
// 	glDrawArrays(GL_TRIANGLES, 0, 3);
// 	CHECK_GL_ERROR();

	glFlush();
	glutSwapBuffers();
	CHECK_GL_ERROR();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

int main(int argc,char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	/* add command line argument "classic" for a pre-3.x context */
	if ((argc != 2) || (strcmp (argv[1], "classic") != 0)) {
		glutInitContextVersion (3, 1);
		glutInitContextFlags ( GLUT_DEBUG);
	}
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	dumpInfo();
	
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		LOG_ERROR("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	CHECK_GL_ERROR();
	shareGLShaderManager()->init();

	pointTest();
	macroTest();
	fielTest();
	glShaderTest();
	virMutilTest();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	system("pause");
	return 0;
}