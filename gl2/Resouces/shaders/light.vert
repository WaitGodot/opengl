//light vertex shader
#version 140

struct LightAttribute
{
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	vec4 m_position;
	vec3 m_spot_dirction;
	float m_spot_exponent;
	float m_spot_cutoff;
	float m_constant_attenuation;
	float m_linear_attenuation;
	float m_quadratic_attenuation;
};

struct LightModeAttribute
{
	vec4 m_model_ambient;
};

struct LightMaterialAttribute
{
	vec4 m_m_ambient;
	vec4 m_m_diffuse;
	vec4 m_m_specular;
	vec4 m_m_emission;
	float m_m_shininess;
};


attribute vec4 a_position; //坐标
attribute vec4 a_color; //颜色
attribute vec3 a_normal; // 法向量

uniform mat4 u_mvMatrix;// 模型视图矩阵
uniform mat4 u_mvpMatrix;//模型视图透视矩阵
//uniform mat3 u_Normal;// 模型视图矩阵的 rotation

LightAttribute u_light;
LightModeAttribute u_light_mode;
LightMaterialAttribute u_light_material;

out vec4 v_varyingFragColor;

void getEyeSpace(out vec3 norm, out vec4 position)
{
	norm =  normalize(u_mvMatrix * vec4(a_normal,0.0));
	position = u_mvMatrix * a_position;
}

vec4 ads(vec3 norm,vec4 position)
{
	vec4 ambient_color = u_light_material.m_m_emission + u_light_mode.m_model_ambient * u_light_material.m_m_ambient;
	u_light.m_position
	float att = 1/
}

void main()
{
	gl_Position = u_ModelViewProject * a_position;
	
	
	float attenuation = 1/()
	vec4 spot_color = 
	v_varyingFragColor = a_color;
}
