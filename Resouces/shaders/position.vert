//position vertex shader
#version 330

attribute vec4 a_position;

void main()
{
	gl_Position = a_position;
}