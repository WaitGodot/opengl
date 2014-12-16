
#version 140

out vec4 vFragColor;

in vec4 varyingTexCoord;

uniform sampler2D vTexture;

void main()
{
	vFragColor = texture2D(vTexture,varyingTexCoord.st);
}
