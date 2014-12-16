//position vertex shader
#version 140

attribute vec4 a_position;
attribute vec4 a_color;

uniform vec4 u_color;
//uniform float u_pointSize;

uniform mat4 u_mvpMatrix;

out vec4 varyingFragColor;

void main()
{
	//gl_PointSize = u_pointSize;
	gl_Position = u_mvpMatrix * a_position;
	varyingFragColor = u_color;
}
