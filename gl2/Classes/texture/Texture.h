#ifndef _CX_TEXTURE_H
#define _CX_TEXTURE_H
#include "gl/glew.h"
#include <gl/gl.h>


class Image;
class Texture
{
public:
	static Texture* create(Image* image,bool mipMaps = false);
	

	//////////////////////////////////////////////////////////////////////////
	//inline
	GLuint getId()const{
		return m_id;
	}
	int getWidth()const{
		return m_width;
	}
	int getHeight()const{
		return m_height;
	}
	//////////////////////////////////////////////////////////////////////////
	Texture();
	~Texture();
private:
	GLuint m_id;
	int m_width;
	int m_height;
	//
	bool initWithImage(Image* image,bool mipMaps);

};
#endif