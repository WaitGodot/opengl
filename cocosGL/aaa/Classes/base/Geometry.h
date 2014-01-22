#ifndef _GEOMETRY_H
#define _GEOMETRY_H

class Color;
namespace cxGeomety{


	class Point
	{
	public:
		float x,y,z;

		Point();
		Point(float x, float y,float z);
		~Point();

		bool operator==(const Point& pt);
		Point operator+(const Point& pt);
		Point operator-(const Point& pt);
		Point operator*(const float& scale);
		Point operator/(const float& scale);

		void render();

// 		virtual void point_virtual(){
// 
// 		}
	};

#define Point2f(x,y) Point((x),(y),(0))
#define Point3f(x,y,z) Point((x),(y),(z))

	class Size
	{
	public:
		float width,height;

		Size();
		Size(float w,float h);
		~Size();

		bool operator==(const Size& sz);
		Size operator+(const Size& sz);
		Size operator-(const Size& sz);
		Size operator*(const float& scale);
		Size operator/(const float& scale);

	};

#define size2f(w,h) Size(w,h)

	class Line
	{
	public:
		Point origin,destination;

		Line();
		Line(const Point& origin , const Point& destination);
		~Line();
	};
#define line2P(origin , destination) Line( (origin) , (destination))
	void sg_renderLine(const Line& rl);
	void sg_randerStripLine(int number,...);//
	void sg_randerLoopLine(int number,...);//
	void sg_randerStripLine(int number,Point* arr);//
	void sg_randerLoopLine(int number,Point* arr);//


	class Triangle
	{
	public:
		Point vertex1,vertex2,vertex3;

		Triangle();
		Triangle(const Point& pt1,const Point& pt2,const Point& pt3);
		~Triangle();
	};
#define triangle3P(p1,p2,p3) Triangle(p1,p2,p3)
	void sg_renderTriangle(const Triangle& triangle);
	void sg_randerTrianglStrip(int number,...);
	void sg_randerTrianglStrip(int number,Point* arr);
	void sg_randerTrianglFan(int number,...);
	void sg_randerTrianglFan(int number,Point* arr);

	class Rect
	{
	public:
		Point origin;
		Point  destination;

		Rect();
		Rect(const Point& pt , const Point& dt);
		~Rect();

		bool intersertRect(const Rect& rt);

	};

#define rect2P(origin,dt) Rect(origin,dt)
	void sg_renderRect(const Rect& rt , bool isFill = false);
	void sg_randerRect(Point* vertex, bool isFill = false);
	void sg_randerRect(Point* vertex, int numbOfPoint,bool isFill = false);

	void drawColor(float r,float g,float b,float a);

	void drawCube(float s);
	void drawSphere(float rudis,int slices,int stacks);
}

#endif