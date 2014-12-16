#ifndef _COLOR_H
#define _COLOR_H

#include <gl/glew.h>

class Color
{
public:
	GLbyte r,g,b,a;

	Color();
	Color(float r, float g,float b,float a = 1);
	Color(GLbyte r,GLbyte g,GLbyte b, GLbyte a = 255);
	~Color();

	float fR();
	float fG();
	float fB();
	float fA();

};

#define color3f(r,g,b)		Color((r),(g),(b))
#define color4f(r,g,b,a)	Color((r),(g),(b),(a))
#define color3b(r,g,b)		Color((r),(g),(b))
#define color4b(r,g,b,a)	Color((r),(g),(b),(a))


#endif