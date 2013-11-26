#include "GLShaderProgram.h"
#include "_MacroConfig.h"

namespace glShaderSpace {


	GLShaderProgram::GLShaderProgram():
		m_programIdentity(0)
	{

	}

	
	GLShaderProgram::~GLShaderProgram()
	{
		//delete program
		if(m_programIdentity!=0){
			glDeleteProgram( m_programIdentity );
		}
	}

	bool GLShaderProgram::initWithVertexShaderByteArray( const GLchar* verterArray ,const GLchar* fragArray )
	{
		bool result = false;
		do 
		{
			BREAK_IF(verterArray == NULL || fragArray == NULL);
			m_programIdentity = glCreateProgram();
			BREAK_IF_LOG(m_programIdentity == 0,"create program error id = %d",m_programIdentity);
			GLint vertexId,fragId;
			BREAK_IF(compile(vertexId,GL_VERTEX_SHADER,verterArray));
			BREAK_IF(compile(fragId,GL_FRAGMENT_SHADER,fragArray));

			glAttachShader(m_programIdentity,vertexId);
			glAttachShader(m_programIdentity,fragId);
			BREAK_IF(link());

			result = true;
		} while (0);

		return result;
	}

	bool GLShaderProgram::compile( GLint& shaderId,GLenum type , const GLchar* array )
	{
		if(!array){
			return false;
		}

		shaderId = glCreateShader(type);
		glShaderSource( shaderId , 1 , &array , NULL);
		CHECK_GL_ERROR();
		glCompileShader(shaderId);
		CHECK_GL_ERROR();
		GLint status;
		glGetShaderiv(shaderId , GL_COMPILE_STATUS,&status);

		if(GL_FALSE == status)
		{
			GLint lengthLog = 0;
			glGetShaderiv(shaderId , GL_INFO_LOG_LENGTH,&lengthLog);
			char* errLog = (char*)malloc( lengthLog);
			glGetShaderInfoLog( shaderId, lengthLog , NULL , errLog);
			LOG_ERROR("compile error log : %s",errLog);
		}
		return (GL_TRUE ==  status);
	}

	bool GLShaderProgram::link()
	{
		GLint status;
		glLinkProgram(m_programIdentity);
		glGetProgramiv(m_programIdentity , GL_LINK_STATUS ,&status);

		if( GL_FALSE == status)
		{
			GLint logLength = 0;
			glGetProgramiv( m_programIdentity ,GL_INFO_LOG_LENGTH ,& logLength);
			char* errLog = (char*)malloc(logLength);
			glGetProgramInfoLog(m_programIdentity,logLength,NULL,errLog);
			LOG_ERROR("link error log : %s",errLog);
		}

		return (GL_TRUE == status);
	}

	GLint GLShaderProgram::getAttribLocation( const char* attribName )
	{
		return glGetAttribLocation(m_programIdentity,(const GLchar*)(attribName));
	}

	GLint GLShaderProgram::getUniformLocation( const char* uniformName )
	{
		return glGetUniformLocation(m_programIdentity,(const GLchar*)(uniformName));
	}



}