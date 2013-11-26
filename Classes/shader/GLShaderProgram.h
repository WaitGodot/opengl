#ifndef _GL_SHADER_PROGRAM_H
#define _GL_SHADER_PROGRAM_H

#include <gl/glew.h>


namespace glShaderSpace{


#define AttributePosition "a_position"
#define AttributeColor "a_color"
#define AttributeTexCoords "a_texCoords"

	enum VertexAttLoction{
		_Vertex_Position,
		_Vertex_Color,
		_Vertex_texCoords,

		_Vertxt_Count,//max :0~15
		_Vertex_Start = _Vertex_Position,
		_Vertex_End = _Vertxt_Count,
	};


	class GLShaderProgram 
	{
		GLuint m_programIdentity;
		GLint m_glLoction[_Vertxt_Count];

	public:
		GLShaderProgram();
		~GLShaderProgram();

		bool initWithVertexShaderByFile(const char* vertexFile,const char* fragmentFile);
		bool initWithVertexShaderByteArray(const GLchar* verterArray ,const GLchar* fragArray);
		GLint getAttribLocation(const char* attribName);
		GLint getUniformLocation(const char* uniformName);
		
		GLint getVertexAttLoction(VertexAttLoction attribute);

	private:
		bool compile(GLint& shaderId,GLenum type , const GLchar* array);
		bool link();

	};

}

#endif