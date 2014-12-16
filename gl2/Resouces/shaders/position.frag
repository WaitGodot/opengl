//position fragment shader
#version 140

out vec4 vFragColor;
in vec4 varyingFragColor;

void main()
{
	vFragColor = varyingFragColor;
}
