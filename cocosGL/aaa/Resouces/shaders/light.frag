
#version 140

out vec4 vFragColor;
in vec4 v_varyingFragColor;

void main()
{
	vFragColor = v_varyingFragColor;
}
