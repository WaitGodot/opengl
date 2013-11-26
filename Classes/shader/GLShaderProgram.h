#ifndef _GL_SHADER_PROGRAM_H
#define _GL_SHADER_PROGRAM_H

#include <gl/glew.h>


namespace glShaderSpace{

	
	class GLShaderProgram 
	{
		GLuint m_programIdentity;

	public:
		GLShaderProgram();
		~GLShaderProgram();

		bool initWithVertexShaderByteArray(const GLchar* verterArray ,const GLchar* fragArray);
		GLint getAttribLocation(const char* attribName);
		GLint getUniformLocation(const char* uniformName);
	private:
		bool compile(GLint& shaderId,GLenum type , const GLchar* array);
		bool link();

	};

}

#endif