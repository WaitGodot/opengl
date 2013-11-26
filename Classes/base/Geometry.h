#ifndef _GEOMETRY_H
#define _GEOMETRY_H


namespace cxGeomety{


	class Point
	{
	public:
		float x,y;

		Point();
		Point(float x, float y);
		~Point();

		bool operator==(const Point& pt);
		Point operator+(const Point& pt);
		Point operator-(const Point& pt);
		Point operator*(const float& scale);
		Point operator/(const float& scale);
	};

#define MakePoint(x,y) Point((x),(y))
	static void gs_renderPoint(const Point& pt);

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

#define MakeSize(w,h) Size(w,h)

	class Line
	{
	public:
		Point origin,destination;

		Line();
		Line(const Point& origin , const Point& destination);
		~Line();
	};
#define MakeLine(origin , destination) Line( (origin) , (destination))
	static void gs_renderLine(const Line& rl);


	class Triangle
	{
	public:
		Point vertex1,vertex2,vertex3;

		Triangle();
		Triangle(const Point& pt1,const Point& pt2,const Point& pt3);
		~Triangle();
	};
#define MakeTriangle(p1,p2,p3) Triangle(p1,p2,p3)
	static void gs_renderTriangle(const Triangle& triangle);

	class Rect
	{
	public:
		Point origin;
		Size  size;

		Rect();
		Rect(const Point& pt , const Size& sz);
		~Rect();

		bool intersertRect(const Rect& rt);

	};

#define MakeRect(origin,size) Rect(origin,size)
	static void gs_renderRect(const Rect& rt);

}

#endif