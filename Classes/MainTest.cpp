#include <gl/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include "_MacroConfig.h"

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

int main(int argc,char** argv)
{
	pointTest();
	macroTest();

	system("pause");
	return 0;
}