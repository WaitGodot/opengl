
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include "GLTools/include/GLTools.h"

using namespace std;



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

}

GLBatch cube;

static void testInit() 
{
	gltMakeCube(cube,1);
}
static void display()
{
	glClearColor(0,0.4,0.6,1);
	glClear(GL_COLOR_BUFFER_BIT);  

	cube.Draw();
	
	glFlush();
	glutSwapBuffers();
}

static void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
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
		exit(EXIT_FAILURE);
	}

	testInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMotionFunc(motionFunction);
	glutMouseFunc(mouseFunction);

	glEnable(GL_MULTISAMPLE);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);


	glutMainLoop();

	system("pause");
	return 0;
}