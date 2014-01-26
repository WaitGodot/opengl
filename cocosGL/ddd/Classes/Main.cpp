#include "gl/glut.h"

#define MODE_NONE 0
#define MODE_LINEAR 1
#define MODE_EXP 2
#define MODE_EXP2 3

GLint fogMode;

// void Initialization(void);
// void OnDisplay(void);
// void OnReShape(int,int);
// void OnMenu(int);
// void CreateMenu(void);
// void DrawTeapot(GLfloat,GLfloat,GLfloat);



void Initialization(void)
{
	GLfloat position[]={0.5f,0.5f,3.0f,0.0f};
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0,GL_POSITION,position); //设置光源位置


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{
		//为材质指定对光源的反射
		GLfloat ambLight[3]={0.17f,0.11f,0.11f};
		glMaterialfv(GL_FRONT,GL_AMBIENT,ambLight); 
		GLfloat difLight[3]={0.61f,0.24f,0.24f};
		glMaterialfv(GL_FRONT,GL_DIFFUSE,difLight);
		GLfloat speLight[3]={0.73f,0.63f,0.63f};
		glMaterialfv(GL_FRONT,GL_SPECULAR,speLight);
		//设置反光系数
		glMaterialf(GL_FRONT,GL_SHININESS,100.0f);  
	}





	glEnable(GL_FOG);//启用雾功能

	GLfloat fogColor[4]={0.5f,0.5f,0.5f,1.0f};
	fogMode=GL_LINEAR;                    
	glFogi(GL_FOG_MODE,fogMode);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.35f);
	glHint(GL_FOG_HINT,GL_DONT_CARE);
	glFogf(GL_FOG_START,1.0f);
	glFogf(GL_FOG_END,5.0f);

	glClearColor(fogColor[0],fogColor[1],fogColor[2],fogColor[3]);//背景色

}

void DrawTeapot(GLfloat x,GLfloat y,GLfloat z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidTeapot(0.8f);
	glPopMatrix();
}

void OnDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawTeapot(-2.0f,-1.0f,-1.0f);
	DrawTeapot(-1.0f,-0.5f,-2.0f);
	DrawTeapot(0.0f,0.0f,-3.0f);
	DrawTeapot(1.0f,0.5f,-4.0f);
	DrawTeapot(2.0f,1.0f,-5.0f);

	glFlush();

}

void OnReShape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);

	glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式
	glLoadIdentity();

	GLfloat aspect =GLfloat(h)/GLfloat(w);

	if(w<=h)
		glOrtho(-2.5f,2.5f,-2.5f*aspect,2.5f*aspect,-10.0f,10.0f);//三维正交投影
	else
		glOrtho(-2.5f/aspect,2.5f/aspect,-2.5f,2.5f,-10.0f,10.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void CreateMenu123(void)
{
	glutAddMenuEntry("线性",MODE_LINEAR);
	glutAddMenuEntry("指数",MODE_EXP);
	glutAddMenuEntry("指数2",MODE_EXP2);
	glutAddMenuEntry("无雾",MODE_NONE);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void OnMenu(int value)
{
	switch (value)
	{
	case MODE_LINEAR:
		fogMode=GL_LINEAR;
		break;

	case MODE_EXP:
		fogMode=GL_EXP;
		break;

	case MODE_EXP2:
		fogMode=GL_EXP2;
	}

	glFogi(GL_FOG_MODE,fogMode);
	if (value==MODE_NONE)
		glDisable(GL_FOG);
	else
		glEnable(GL_FOG);

	glutPostRedisplay();
}

void main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutCreateWindow("OpenGL雾化");

	glutReshapeFunc(OnReShape);
	glutDisplayFunc(OnDisplay);
	glutCreateMenu(OnMenu);

	CreateMenu123();
	Initialization();

	glutMainLoop();
}