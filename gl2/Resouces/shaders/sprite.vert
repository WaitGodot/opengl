//sprite vertex shader
#version 140

attribute vec4 a_position;
attribute vec4 a_texCoords;


uniform mat4 u_mvpMatrix;

out vec4 varyingTexCoord;

void main()
{
	gl_Position = u_mvpMatrix * a_position;
	varyingTexCoord = a_texCoords;
}
