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
#define LOG_ERROR(format,...) 
#else
#define LOG_ERROR(format,...)	fprintf(stderr,format,##__VA_ARGS__);\
	fprintf(stderr,"\n");
#endif

#if !defined(_MACRO_SWITCH) 
#define LOG(format,...) 
#else
#define LOG(format,...)	fprintf(stdout,format,##__VA_ARGS__);\
	fprintf(stdout,"\n");
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

#ifndef RETURN_IF
#define RETURN_IF(_VALUE_)	if (_VALUE_){return;}
#endif

#ifndef RETURN_IF_LOG
#define RETURN_IF_LOG(_VALUE_,format,...) if(_VALUE_){ LOG_ERROR(format,##__VA_ARGS__);return;}
#endif

#ifndef DELETE_SAFE
#define DELETE_SAFE(p) if(p){delete p ; p = 0;}
#endif

#ifndef DELETE_ARRAY_SAFE
#define DELETE_ARRAY_SAFE(p) if(p){delete [] p ; p = 0;}
#endif

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f


#ifndef PI
#define PI (3.14159265358979323846)
#define PER_DEGREE (PI/180.0)
#define DEGREE(angle) (PER_DEGREE*(angle))
#endif

#define PVCLASSDATA
#ifndef PVCLASSDATA
#define PVCLASSDATA(c)  ((unsigned char*)(c) + 4 )
#endif

#define VCLASSDATA
#ifndef VCLASSDATA
#define VCLASSDATA(c)  ((unsigned char*)(&c) + 4 )
#endif

#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.

#endif