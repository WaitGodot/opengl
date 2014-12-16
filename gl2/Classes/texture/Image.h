#ifndef _IMAGE_H
#define _IMAGE_H



class Image
{

public:

	typedef enum _ImageFormat
	{
		FmtPng, 
		FmtRGB,
		FmtRGBA,

	}ImageFormat;

	typedef enum _Format{
		FRGB,
		FRGBA,
	}Format;

	//////////////////////////////////////////////////////////////////////////
	//inline
	inline Format format()const{
		return m_format;
	}
	inline ImageFormat imageFormat()const{
		return m_imageFormat;
	}
	inline unsigned int imageWidth()const{
		return m_width;
	}
	inline unsigned int imageHeight()const{
		return m_height;
	}
	inline unsigned char* imageData()const{
		return m_data;
	}
	//////////////////////////////////////////////////////////////////////////

	Image();
	~Image();

	static Image* create(const char* file,ImageFormat _format = FmtPng);
	static Image* create(unsigned char* data,unsigned long datalength,ImageFormat _format = FmtPng);
	static Image* createWithRGBData(unsigned char* data,unsigned int width,unsigned int height,ImageFormat _format = FmtRGB);
private:
	Format m_format;
	ImageFormat m_imageFormat;
	unsigned int m_width;
	unsigned int m_height;
	unsigned char* m_data;

	Image& operator=(const Image& rhs);

	bool initWithData(unsigned char* data,unsigned long datalength,ImageFormat _format);
	bool initPng(unsigned char* data,unsigned long datalength);
};
#endif