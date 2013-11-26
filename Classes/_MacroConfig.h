#ifndef _MACRO_CONFIG_H
#define _MACRO_CONFIG_H
#include <iostream>
#include <gl/glew.h>

//macro
// #ifndef _MACRO_SWITCH
// #define _MACRO_SWITH 0
// #endif
#define _MACRO_SWITCH

#if !defined(_MACRO_SWITCH) 
#define LOG_ERROR()
#else
#define LOG_ERROR(format,...)	fprintf(stderr,format,##__VA_ARGS__);\
	fprintf(stderr,"\n");
#endif

#if !defined(_MACRO_SWITCH) 
#define CHECK_GL_ERROR()
#else
#define CHECK_GL_ERROR() \
	do\
	{\
		GLenum err = glGetError();\
		if(err){\
		LOG_ERROR( "OpenGL error 0x%04X in File:%s ,Function Name:%s ,Line:%d", err, __FILE__, __FUNCTION__, __LINE__);\
		}\
	} while (0);
#endif


#ifndef BREAK_IF
#define BREAK_IF(_VALUE_)	if (_VALUE_){break;}
#endif

#ifndef BREAK_IF_LOG
#define BREAK_IF_LOG(_VALUE_,format,...) if(_VALUE_){ LOG_ERROR(format,##__VA_ARGS__);break;}
#endif


#endif