#ifndef _GL_SHADER_PROGRAM_H
#define _GL_SHADER_PROGRAM_H

#include <gl/glew.h>
#include <gl/GL.h>
#include "GLLight.h"


namespace glShaderSpace{


#define AttributePosition "a_position"
#define AttributeColor "a_color"
#define AttributeTexCoords "a_texCoords"
#define AttributeNormal "a_normal"

	enum VertexAttLoction{
		_Vertex_Position,
		_Vertex_Color,
		_Vertex_texCoords,
		_Vertex_Normal,

		_Vertxt_Count,//max :0~15
		_Vertex_Start = _Vertex_Position,
		_Vertex_End = _Vertxt_Count,
	};


#define UniformColor "u_color"
#define UniformPointSize "u_pointSize"
#define UniformMvMatrix "u_mvMatrix"
#define UniformMvpMatrix "u_mvpMatrix"
#define UniformNormal "u_Normal"
#define UniformTexture "vTexture"

	enum VertexUniformLoction{
		U_COLOR,
		U_POINTSIZE,
		U_MVMATRIX,
		U_MVPMATRIX,
		U_NORMAL,
		U_TEXTURE,

		U_MAX,
	};


#define LIGHT_COUNT 16


	class GLShaderProgram 
	{
		GLuint m_programIdentity;
		GLint m_glAttributeLoction[_Vertxt_Count];
		GLint m_glUniformLoction[U_MAX];
		GLLight* m_glLight[LIGHT_COUNT];
		int m_lightCount;
	public:
		GLShaderProgram();
		~GLShaderProgram();

		static GLShaderProgram* createByFile(const char* vertexFile,const char* fragmentFile);
		static GLShaderProgram* createByByte(const GLchar* verterArray ,const GLchar* fragArray);

		bool initWithVertexShaderByFile(const char* vertexFile,const char* fragmentFile);
		bool initWithVertexShaderByteArray(const GLchar* verterArray ,const GLchar* fragArray);

		GLint getVertexAttLoction(VertexAttLoction attribute);
		GLint getVertexUniformLoction(VertexUniformLoction uniform);

		GLLight* getGlLight(int position = 0);
		void addGLLight(GLLight* light);

		GLint getProgram()const;

		void use();
		void updateMVMatrix();
		void updateMVPMatrix();
		void updateAllLight();

	private:
		bool compile(GLint& shaderId,GLenum type , const GLchar* array);
		bool link();
		void updateUniforms();

		friend class GLShaderMgr;

	};

}

#endif