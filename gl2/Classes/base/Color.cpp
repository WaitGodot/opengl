#include "Color.h"

Color::Color()
{
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->a = 255;
}

Color::Color( float r, float g,float b,float a /*= 1*/ )
{
	this->r = r * 255;
	this->g = g * 255;
	this->b = b * 255;
	this->a = a * 255;
}

Color::Color( GLbyte r,GLbyte g,GLbyte b, GLbyte a /*= 255*/ )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::~Color()
{

}

float Color::fR()
{
	return this->r / 255.0f;
}

float Color::fG()
{
	return this->g / 255.0f;
}

float Color::fB()
{
	return this->b / 255.0f;
}

float Color::fA()
{
	return this->a / 255.0f;
}

