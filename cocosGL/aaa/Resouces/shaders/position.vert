//position vertex shader
#version 140

attribute vec4 a_position;
attribute vec4 a_color;

uniform vec4 u_color;
uniform float u_pointSize;

uniform mat4 u_ModelViewMatrix;

out vec4 v_varyingFragColor;

void main()
{
	gl_PointSize = u_pointSize;
	gl_Position = u_ModelViewMatrix * a_position;
	v_varyingFragColor = u_color;
}
