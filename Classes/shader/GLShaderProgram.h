#ifndef _GL_SHADER_PROGRAM_H
#define _GL_SHADER_PROGRAM_H

#include <gl/glew.h>
#include <gl/GL.h>


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


#define Uniform_U_COLOR "u_color"
#define Uniform_U_POINTSIZE "u_pointSize"

	enum VertexUniformLoction{
		U_COLOR,
		U_POINTSIZE,

		U_MAX,
	};


	class GLShaderProgram 
	{
		GLuint m_programIdentity;
		GLint m_glAttributeLoction[_Vertxt_Count];
		GLint m_glUniformLoction[U_MAX];

	public:
		GLShaderProgram();
		~GLShaderProgram();

		static GLShaderProgram* createByFile(const char* vertexFile,const char* fragmentFile);
		static GLShaderProgram* createByByte(const GLchar* verterArray ,const GLchar* fragArray);

		bool initWithVertexShaderByFile(const char* vertexFile,const char* fragmentFile);
		bool initWithVertexShaderByteArray(const GLchar* verterArray ,const GLchar* fragArray);

		GLint getVertexAttLoction(VertexAttLoction attribute);
		GLint getVertexUniformLoction(VertexUniformLoction uniform);

		GLint getProgram()const;
		void use();
	private:
		bool compile(GLint& shaderId,GLenum type , const GLchar* array);
		bool link();

	};

}

#endif