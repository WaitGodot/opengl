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


static GLfloat sg_rotateX = 0.0f;
static GLfloat sg_rotateY = 0.0f;
static int sg_mouseX = 0;
static int sg_mouseY = 0;

static void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

static void drawAxis()
{
	cxGLPushMatrix();
	{
		drawColor(1,0,0,1);
		sg_renderLine(line2P(Point3f(-4,0,0),Point3f(4,0,0)));
		drawColor(0,1,0,1);
		sg_renderLine(line2P(Point3f(0,-4,0),Point3f(0,4,0)));
		drawColor(0,0,1,1);
		sg_renderLine(line2P(Point3f(0,0,-4),Point3f(0,0,4)));
		drawColor(1,1,1,1);
	}

	cxGLPopMatrix();
}

static void display()
{
	glClearColor(0,0.4,0.6,1);
	glClear(GL_COLOR_BUFFER_BIT);  

	cxGLMatrixMode(CXGL_VIEWMODE);

	cxGLPushMatrix();
	{
		cxGLRotatef(sg_rotateX,1,0,0);
		cxGLRotatef(sg_rotateY,0,1,0);
		//drawAxis();
		
		//lightningTest();
		cubeTest();
		
		//lightTest();
	}
	cxGLPopMatrix();

	glFlush();
	glutSwapBuffers();
	CHECK_GL_ERROR();
}

static void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	cxGLMatrixMode(CXGL_PROJECT);
	cxGLLoadentity();
	cxGLPerspectiveProjection(60,w/h,1,10);

	cxGLMatrixMode(CXGL_VIEWMODE);
	cxGLLoadentity();
	cxGLLookAt(0,0,8,0,0,-1,0,1,0);
}

static void idle(void)
{
	glutPostRedisplay();
}


static void motionFunction(int x, int y)
{
	sg_rotateY += (x - sg_mouseX);
	sg_rotateX += (y - sg_mouseY);

	sg_mouseX = x;
	sg_mouseY = y;
}

static void mouseFunction(int button,int state,int x,int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
		{
			sg_mouseX = x;
			sg_mouseY = y;
		}
		break;
	default:
		break;
	}
}
int main(int argc,char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	/* add command line argument "classic" for a pre-3.x context */
	if ((argc != 2) || (strcmp (argv[1], "classic") != 0)) {
		glutInitContextVersion (3, 1);
		glutInitContextFlags ( GLUT_DEBUG);
	}
	glutInitWindowSize (800, 480); 
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
	// 
	// 	GLint maxVertexUniforms;
	// 	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniforms);
	// 	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &maxVertexUniforms);
	// 	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxVertexUniforms);

	lightInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMotionFunc(motionFunction);
	glutMouseFunc(mouseFunction);

	glEnable(GL_MULTISAMPLE);

 	glEnable(GL_CULL_FACE);
 	glCullFace(GL_BACK);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	
	glutMainLoop();

	system("pause");
	return 0;
}