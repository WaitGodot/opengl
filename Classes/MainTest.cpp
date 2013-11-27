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

using namespace cxGeomety;

void pointTest()
{
	Point pt;
	pt = MakePoint(1,1);
	Point pt1 = MakePoint(2,2);

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

void display()
{
	glClearColor(0,0,1,1);

	glFlush();
	CHECK_GL_ERROR();
}

int main(int argc,char** argv)
{

	glutInitWindowSize(300,300);
	glutInitWindowPosition(300,300);
	glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitContextVersion (3, 1);
	glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
	glutCreateWindow("Main");
	dumpInfo();
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		LOG_ERROR("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	pointTest();
	macroTest();
	fielTest();
	glShaderTest();

	glutDisplayFunc(display);
	glutMainLoop();

	system("pause");
	return 0;
}