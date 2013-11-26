#include "GLShaderProgram.h"
#include "_MacroConfig.h"

namespace glShaderSpace {


	GLShaderProgram::GLShaderProgram():
		m_programIdentity(0)
	{
		for(int i = _Vertex_Start ; i < _Vertex_End ; i ++)
		{
			m_glLoction[i] = -1;
		}
	}

	
	GLShaderProgram::~GLShaderProgram()
	{
		//delete program
		if(m_programIdentity!=0){
			glDeleteProgram( m_programIdentity );
		}
	}

	bool GLShaderProgram::initWithVertexShaderByFile( const char* vertexFile,const char* fragmentFile )
	{

		return false;
	}

	bool GLShaderProgram::initWithVertexShaderByteArray( const GLchar* verterArray ,const GLchar* fragArray )
	{
		bool result = false;
		GLint vertexId = 0,fragId =0;
		do 
		{
			BREAK_IF(verterArray == NULL || fragArray == NULL);
			m_programIdentity = glCreateProgram();
			BREAK_IF_LOG(m_programIdentity == 0,"create program error id = %d",m_programIdentity);
			BREAK_IF(compile(vertexId,GL_VERTEX_SHADER,verterArray));
			BREAK_IF(compile(fragId,GL_FRAGMENT_SHADER,fragArray));

			glAttachShader(m_programIdentity,vertexId);
			glAttachShader(m_programIdentity,fragId);
			BREAK_IF(link());

			m_glLoction[_Vertex_Position] = glGetAttribLocation(m_programIdentity,AttributePosition);
			m_glLoction[_Vertex_Color]    = glGetAttribLocation(m_programIdentity,AttributeColor);
			m_glLoction[_Vertex_texCoords]= glGetAttribLocation(m_programIdentity,AttributeTexCoords);

			result = true;
		} while (0);

		glDeleteShader(vertexId);
		glDeleteShader(fragId);

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

	GLint GLShaderProgram::getVertexAttLoction( VertexAttLoction attribute )
	{
		_ASSERT( attribute >= 0 && attribute <= _Vertxt_Count;"getVertexAttLoction error!");
		return m_glLoction[attribute];
	}




}