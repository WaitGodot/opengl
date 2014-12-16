#include "Image.h"
#include "MacroConfig.h"
#include "file/Fileutils.h"
#include "png.h"
#include <iostream>
#include <memory>

using namespace std;


Image::Image():
m_data(0),m_imageFormat(FmtPng),m_height(0),m_width(0)
{

}

Image::~Image()
{
	DELETE_ARRAY_SAFE(m_data);
}

Image* Image::create( const char* file,ImageFormat _format /*= FmtPng*/ )
{
	unsigned long length = 0;
	unsigned char* data = gsShareFileUtils()->getFileData(file,"rb",length);
	return Image::create(data,length,_format);
}

Image* Image::create( unsigned char* data,unsigned long datalength,ImageFormat _format /*= FmtPng*/ )
{
	Image* ig = new Image();
	if (ig && ig->initWithData(data,datalength,_format))
	{
		return ig;
	}
	DELETE_SAFE(ig);
	return NULL;
}

Image* Image::createWithRGBData( unsigned char* data,unsigned int width,unsigned int height,ImageFormat _format /*= FmtRGB*/ )
{
	Image* ig = new Image();
	ig->m_width = width;
	ig->m_height = height;
	ig->m_imageFormat = _format;
	ig->m_data = data;
	switch(_format){
	case FmtRGB:
		ig->m_format = FRGB;
		break;
	case FmtRGBA:
		ig->m_format = FRGBA;
		break;
	default:
		break;;
	}
	return ig;
}


bool Image::initWithData( unsigned char* data,unsigned long datalength,ImageFormat _format )
{
	bool res = false;
	do 
	{
		BREAK_IF(data == NULL || datalength == 0);
		m_imageFormat = _format;
		switch(m_imageFormat){
		case FmtPng:
			res = initPng(data,datalength);
			break;
		default:
			res = false;
			break;
		}
	} while (0);
	DELETE_ARRAY_SAFE(data);

	return res;
}


// such as RGB888, RGB5A1
#define CC_RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
	((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
	((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
	((unsigned)(unsigned char)(va) << 24))

// on ios, we should use platform/ios/CCImage_ios.mm instead

typedef struct 
{
	unsigned char* data;
	int size;
	int offset;
}tImageSource;

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

	if((int)(isource->offset + length) <= isource->size)
	{
		memcpy(data, isource->data+isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

bool Image::initPng( unsigned char* data,unsigned long datalength )
{
	// length of bytes to check if it is a valid png file
#define PNGSIGSIZE  8
	bool bRet = false;
	png_byte        header[PNGSIGSIZE]   = {0}; 
	png_structp     png_ptr     =   0;
	png_infop       info_ptr    = 0;

	do 
	{
		// png header len is 8 bytes
		BREAK_IF(datalength < PNGSIGSIZE);

		// check the data is png or not
		memcpy(header, data, PNGSIGSIZE);
		BREAK_IF(png_sig_cmp(header, 0, PNGSIGSIZE));

		// init png_struct
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		BREAK_IF(! png_ptr);

		// init png_info
		info_ptr = png_create_info_struct(png_ptr);
		BREAK_IF(!info_ptr);


		// set the read call back function
		tImageSource imageSource;
		imageSource.data    = (unsigned char*)data;
		imageSource.size    = datalength;
		imageSource.offset  = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		// Read the entire image into memory.
		png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

		m_width = png_get_image_width(png_ptr, info_ptr);
		m_height = png_get_image_height(png_ptr, info_ptr);

		png_byte colorType = png_get_color_type(png_ptr, info_ptr);
		switch (colorType)
		{
		case PNG_COLOR_TYPE_RGBA:
			m_format = FRGBA;
			break;

		case PNG_COLOR_TYPE_RGB:
			m_format = FRGB;
			break;

		default:
			png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
			return bRet;
		}

		size_t stride = png_get_rowbytes(png_ptr, info_ptr);

		// Allocate image data.
		m_data = new unsigned char[stride * m_height];

		// Read rows into image data.
		png_bytepp rows = png_get_rows(png_ptr, info_ptr);
		for (unsigned int i = 0; i < m_height; ++i)
		{
			memcpy(m_data+(stride * (m_height-1-i)), rows[i], stride);
		}

		bRet = true;
	} while (0);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}
	

	return bRet;
}


