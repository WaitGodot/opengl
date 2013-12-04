//position vertex shader
#version 140

attribute vec4 a_position;
attribute vec4 a_color;

out vec4 v_varyingFragColor;

void main()
{
	gl_PointSize = 2.0;
	gl_Position = a_position;
	v_varyingFragColor = a_color;
}
