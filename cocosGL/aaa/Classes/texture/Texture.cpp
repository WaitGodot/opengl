#include "Texture.h"
#include "Image.h"
#include "MacroConfig.h"

Texture::Texture():
m_id(0)
{

}

Texture::~Texture()
{
	if (m_id)
	{
		glDeleteTextures(1,&m_id);
	}
}

Texture* Texture::create( Image* image,bool mipMaps /*= false*/ )
{
	Texture* tx = new Texture();
	if (tx && tx->initWithImage(image,mipMaps))
	{
		return tx;
	}
	DELETE_SAFE(tx);
	return NULL;
}



//////////////////////////////////////////////////////////////////////////
//private
bool Texture::initWithImage( Image* image,bool mipMaps )
{
	bool rt = false;
	do 
	{
		CHECK_GL_ERROR();
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		glGenTextures(1,&m_id);
		BREAK_IF(!m_id || !image);
		glBindTexture(GL_TEXTURE_2D,m_id);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		switch(image->format())
		{
		case Image::FRGB:
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->imageWidth(),image->imageHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,image->imageData());
			break;
		case Image::FRGBA:
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,image->imageWidth(),image->imageHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,image->imageData());
			break;
		default:
			LOG_ERROR("init with image error,image format not define!!");
			return rt;
		}
		
		m_width = image->imageWidth();
		m_height = image->imageHeight();

		CHECK_GL_ERROR();
		rt = true;
	} while (0);

	return rt;
}