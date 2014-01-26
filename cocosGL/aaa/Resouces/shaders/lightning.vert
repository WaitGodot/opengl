
#version 140

attribute vec4 a_position;
uniform mat4 u_mvpMatrix;

uniform vec3  u_resolution;         
uniform float u_globalTime; 

out vec3 iResolution;
out float iGlobalTime;

void main()
{
	gl_Position = u_mvpMatrix * a_position;
	iResolution = u_resolution;
	iGlobalTime = u_globalTime;
	
}
