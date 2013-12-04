#include "GLShaderProgram.h"
#include "_MacroConfig.h"
#include "file/Fileutils.h"
#include <gl/freeglut.h>

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
		unsigned long length = 0;
		GLchar* vertArray = (GLchar*)gsShareFileUtils()->getFileData( vertexFile,"r",length);
		vertArray[length] = '\0';
		GLchar* fragArray = (GLchar*)gsShareFileUtils()->getFileData( fragmentFile,"r",length);
		fragArray[length] = '\0';
		return initWithVertexShaderByteArray(vertArray,fragArray);
	}


	bool GLShaderProgram::initWithVertexShaderByteArray( const GLchar* verterArray ,const GLchar* fragArray )
	{
		bool result = false;
		GLint vertexId = 0,fragId =0;
		do 
		{
			BREAK_IF(verterArray == NULL || fragArray == NULL);
			CHECK_GL_ERROR();
			BREAK_IF(!compile(vertexId,GL_VERTEX_SHADER,verterArray));
			CHECK_GL_ERROR();
			BREAK_IF(!compile(fragId,GL_FRAGMENT_SHADER,fragArray));
			CHECK_GL_ERROR();

			m_programIdentity = glCreateProgram();
			BREAK_IF_LOG(m_programIdentity == 0,"create program error id = %d",m_programIdentity);
			glAttachShader(m_programIdentity,vertexId);
			glAttachShader(m_programIdentity,fragId);
			BREAK_IF(!link());

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
			std::string str = (type == GL_FRAGMENT_SHADER ? "Fragment shader" : " Vertex shader");
			LOG_ERROR("compile %s error log : \n%s",str.c_str(),errLog);
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
		_ASSERT( attribute >= 0 && attribute <= _Vertxt_Count,"getVertexAttLoction error!");
		return m_glLoction[attribute];
	}

	void GLShaderProgram::use()
	{
		if(m_programIdentity){
			glUseProgram(m_programIdentity);
		}
	}

	GLShaderProgram* GLShaderProgram::createByFile( const char* vertexFile,const char* fragmentFile )
	{
		GLShaderProgram* program = new GLShaderProgram();
		if(!program->initWithVertexShaderByFile(vertexFile,fragmentFile)){
			DELETE_SAFE(program);
		}
		return program;
	}

	GLShaderProgram* GLShaderProgram::createByByte( const GLchar* verterArray ,const GLchar* fragArray )
	{
		GLShaderProgram* program = new GLShaderProgram();
		if(!program->initWithVertexShaderByFile(verterArray,fragArray)){
			DELETE_SAFE(program);
		}
		return program;
	}




}