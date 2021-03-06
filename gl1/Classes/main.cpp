#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>

using namespace std;

#define _MACRO_SWITCH

#if !defined(_MACRO_SWITCH) 
#define LOG_ERROR()
#else
#define LOG_ERROR(format,...)	fprintf(stderr,format,##__VA_ARGS__);\
	fprintf(stderr,"\n");
#define LOG(format,...)		fprintf(stdout,format,##__VA_ARGS__);\
	fprintf(stdout,"\n");
#endif

#if !defined(_MACRO_SWITCH) 
#define CHECK_GL_ERROR()
#else
#define CHECK_GL_ERROR() \
	do\
{\
	GLenum err = glGetError();\
	if(err){\
	LOG_ERROR( "OpenGL error 0x%04X in File:%s ,Function Name:%s ,Line:%d", err, __FILE__, __FUNCTION__, __LINE__);\
	}\
} while (0);
#endif

#define FOLLOWWITHEYE 1
#define FOLLOWWTIHSELF 2
#define FOLLOW FOLLOWWTIHSELF

void dumpInfo(void)
{
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}

static float rotate_f  = 0;
static GLfloat light_position[4] = {0,0,5,1};
static GLfloat light_diffuse[4] = {0.5,0,0,1};
static GLfloat sg_rotateX = 0.0f;
static GLfloat sg_rotateY = 0.0f;
static int sg_mouseX = 0;
static int sg_mouseY = 0;
static GLfloat eye[3] = {0,0,8};

void matrixTest()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(-1,0,-1);
	glVertex3f(1,0,-1); 

	glVertex3f(0,1,-1);
	glVertex3f(0,-1,-1);
	glEnd();
	glPopMatrix();

	glColor3f(1.0,0,0);
	glPushMatrix();

	glTranslated(0.5,-0.5,-3);
	glRotated(rotate_f,0.1,0.1,0.1);
	// 		glRotated(rotate_f,1,0,0.1);
	// 		glRotated(rotate_f,0,1,0.1);

	glScalef(0.5,1,0.5);
	//glutWireSphere (1.0,20,20);
	glutWireCube(1);

	glPopMatrix();

	glColor3f(1.0,0,0);
	glPushMatrix();

	glTranslated(0.5,0.5,-3);
	glRotated(rotate_f,1,1,1);
	// 		glRotated(rotate_f,1,0,0.1);
	// 		glRotated(rotate_f,0,1,0.1);

	glScalef(0.5,1,0.5);
	//glutWireSphere (1.0,20,20);
	glutWireCube(1);

	glPopMatrix();

	glColor3f(1.0,0,0);
	glPushMatrix();

	glTranslated(-0.5,-0.5,-3);
	glRotated(rotate_f,0,0,0.1);
	glRotated(rotate_f,0.1,0,0);
	glRotated(rotate_f,0,0.1,0);

	glScalef(0.5,1,0.5);
	//glutWireSphere (1.0,20,20);
	glutWireCube(1);

	glPopMatrix();

	glColor3f(1.0,1.0,1.0);

	glPushMatrix();

	//glTranslated(0.0,0.0,-3);
	//glRotated(rotate_f,0.1,0,0);
	// 		glLineWidth(2); 
	// 		glBegin(GL_LINES);
	// 		glVertex3f(-0.5,0,-1);
	// 		glVertex3f(0.5,0,-1); 
	// 		glEnd();

	glPopMatrix();
}

void solarSystem()
{
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	{
		glRotated(rotate_f,0,1,0);
		glPushMatrix();
		{
			glColor3f(1,0,0);
			glRotated(90,1,0,0);
			glutWireSphere (1,30,30);
		}
		glPopMatrix();
	}

	{
		glTranslated(5,0,0);
		glRotated(rotate_f,0,1,0);
		
		glPushMatrix();
		{
			glColor3f(0,1,0);
			glRotated(90,-1,1,0);
			glutWireSphere (0.8,20,20);
		}
		glPopMatrix();
		
	}
	{
		glTranslated(2,0,0);
		glRotated(rotate_f,0,1,0);
		glPushMatrix();
		{
			glRotated(90,1,0,0);
			glColor3f(0,0,1);
			glutWireSphere (0.5,10,10);
		}
		glPopMatrix();
		
	}
	glPopMatrix();
}

static void drawAxis()
{
	glPushMatrix();
	{
		GLfloat specular[] = {0,0,0,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
		GLfloat emission[] = {0,0,0,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
		glBegin(GL_LINES);
		//X axis
		GLfloat x_ambient_diffuse[] = {1,0,0,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,x_ambient_diffuse);
		glVertex3f(8,0,0);
		glVertex3f(-8,0,0);
		//y axis
		GLfloat y_ambient_diffuse[] = {0,1,0,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,y_ambient_diffuse);
		glVertex3f(0,8,0);
		glVertex3f(0,-8,0);
		//z axis
		GLfloat z_ambient_diffuse[] = {0,0,1,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,z_ambient_diffuse);
		glVertex3f(0,0,-8);
		glVertex3f(0,0,8);
		glEnd();
// 		GLfloat ambient_diffuse[] = {1,1,1,1};
// 		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,ambient_diffuse);
	}
	glPopMatrix();
}

static void drawLight(GLenum light)
{
#if ( FOLLOW == FOLLOWWTIHSELF)
	//light
	glPushMatrix();
	{
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,light_diffuse);

		glRotated(rotate_f,1,1,0);
		glTranslated(light_position[0],light_position[1],light_position[2]);
		glutSolidSphere(0.1,10,10);
		glLightfv(light,GL_POSITION,light_position);// light position
	}
	glPopMatrix();
#endif
	

}
static void light_test()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{

#if ( FOLLOW == FOLLOWWITHEYE )
		glLoadIdentity();
		gluLookAt(eye[0],eye[1],eye[2],0,0,0,0,1,0);
#endif
		glRotated(sg_rotateX,1,0,0);
		glRotated(sg_rotateY,0,1,0);

		glLightfv(GL_LIGHT0,GL_POSITION,light_position);

		//drawLight(GL_LIGHT0);
		// axis
		//drawAxis();
		//
		glPushMatrix();
		{
			GLfloat sphere_emission[] = {0,0,0,1};
			GLfloat sphere_ambient [] = {0,0,0,1};
			GLfloat sphere_diffuse [] = {0.5,0,0,1};
			GLfloat sphere_specular[] = {0,1,0,1};
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,sphere_ambient);
			
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,sphere_diffuse);
 			
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sphere_specular);
			glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,66);
			
			glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,sphere_emission);
			//glutSolidSphere(1,20,20);
			glRotated(rotate_f,0,0,1);
			glutSolidCube(2);
		}
		glPopMatrix();
	}
	glPopMatrix();

	
}
void robot()
{
	glMatrixMode(GL_MODELVIEW);

	//light
	glPushMatrix();
	{
		//glLoadIdentity();
		glTranslated(light_position[0],light_position[1],light_position[2]);
		glutWireSphere(0.1,10,10);
	}
	glPopMatrix();

	glPushMatrix();
	{
	
		glRotated(sg_rotateX,1,0,0);
		glRotated(sg_rotateY,0,1,0);


		glPushMatrix();
		{
			glBegin(GL_LINES);
			//X axis
			glVertex3f(8,0,0);
			glVertex3f(-8,0,0);
			//y axis
			glVertex3f(0,8,0);
			glVertex3f(0,-8,0);
			//z axis
			glVertex3f(0,0,-8);
			glVertex3f(0,0,8);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
		//	glRotated(60,1,1,0);
			glColor3f(1,0,0);
			glTranslated(1,0,0);
			glRotated(rotate_f,0,0,1);
			glTranslated(-1,0,0);
			glutSolidCube(2);
			//glutWireCube(2);

			glPushMatrix();
			{
				glColor3f(0,1,0);
				glTranslated(1,1,0);
				glRotated(60,0,0,1);
				glTranslated(1,-1,0);
				//glutWireCube(2);
				glutSolidCube(2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void display()
{
	glClearColor(0,0.4,0.6,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	//solarSystem();
	//robot();
	light_test();

// 	glPushMatrix();
// 	glRotated(rotate_f,1,0,0);
// 	glutWireCube(2);
// 	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	CHECK_GL_ERROR();
//	LOG("rotate : %f",rotate_f);
//	rotate_f += 0.1;
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
 	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	//glFrustum(-1,1,-1,1,1,100);
	gluPerspective(60,w/h,1,10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#if ( FOLLOW == FOLLOWWITHEYE )
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);// light position
#else
	gluLookAt(0,0,8,0,0,0,0,1,0);
#endif

}

void initLight()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	GLfloat light_ambient[4] = {0,0,0,1};
	GLfloat light_diffuse[4] = {0.5,0.5,0.5,1};
	GLfloat light_specular[4] = {0,0.5,0.5,1};
	
	GLfloat light_direction[3] = {0,0,-1};

// 	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
// 	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
//	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
//	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,1);
	//glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,20);
//	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light_direction);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,1);
	//GLfloat model_ambient[4] = {0.1,0.1,0.1,1};
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT,model_ambient);

	//GLfloat mat_specular[] = {1,0,0,1};
	//GLfloat mat_shininess [] = { 50 };

	GLfloat mode_ambient[] = {0,0,0,1};
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,mode_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
	LOG("light position: %f,%f,%f",light_position[0],light_position[1],light_position[2]);
}

static void idle(void)
{
	glutPostRedisplay();
}

static void keyFunction(unsigned char key, int x, int y)
{
	switch(key)
	{
		// x
		case 'a':
		case 'A':
			light_position[0] += 1;
			break;
		case 'q':
		case 'Q':
			light_position[0] -= 1;
			break;

			// y
		case 's':
		case 'S':
			light_position[1] += 1;
			break;
		case 'w':
		case 'W':
			light_position[1] -= 1;
			break;

			// z
		case 'd':
		case 'D':
			light_position[2] += 1;
			break;
		case 'e':
		case 'E':
			light_position[2] -= 1;
			break;
			//eye x
		case 'h':
		case 'H':
			eye[0] += 1;
			break;
		case 'Y':
		case 'y':
			eye[0] -= 1;
			break;

			//eye y
		case 'k':
		case 'K':
			eye[1] += 1;
			break;
		case 'I':
		case 'i':
			eye[1] -= 1;
			break;

			//eye z
		case 'l':
		case 'L':
			eye[2] += 1;
			break;
		case 'o':
		case 'O':
			eye[2] -= 1;
			break;
		default:
			break;
	}
	LOG("eye : %f,%f,%f",eye[0],eye[1],eye[2]);
	initLight();
}
static void special (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP: 
		rotate_f ++;
		break;
	case GLUT_KEY_DOWN: 
		rotate_f --;
		break;
	default:
		
		break;
	}

	LOG("rotate : %f",rotate_f);
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
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	if ((argc != 2) || (strcmp (argv[1], "classic") != 0)) {
		glutInitContextVersion (1, 1);
		glutInitContextFlags ( GLUT_DEBUG);
	}
	glutInitWindowSize (800, 480); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("bbb");
	dumpInfo();

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) 
	{
		exit(EXIT_FAILURE);
	}



	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyFunction);
	glutSpecialFunc(special);
	glutMotionFunc(motionFunction);
	glutMouseFunc(mouseFunction);
//	glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;

 	glEnable(GL_CULL_FACE);
 	glCullFace(GL_BACK);

 	glEnable(GL_DEPTH_TEST);
 	glDepthFunc(GL_LESS);
// 	CHECK_GL_ERROR();
//  	glEnable(GL_LINE_SMOOTH );
//   	glHint(GL_LINE_SMOOTH ,GL_NICEST);
//  	glEnable(GL_POLYGON_SMOOTH );
//  	glHint(GL_POLYGON_SMOOTH ,GL_NICEST);

	//glEnable(GL_SMOOTH);
	//CHECK_GL_ERROR();

	initLight();
	glEnable(GL_MULTISAMPLE);
	glutMainLoop();

	_CrtDumpMemoryLeaks () ;

	system("pause");
	return 0;
}