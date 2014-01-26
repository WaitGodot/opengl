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
	float m_spot_coscutoff; // 角度的余弦值 c++中计算
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
//attribute vec4 a_color; //颜色
attribute vec3 a_normal; // 法向量

uniform mat4 u_mvMatrix;// 模型视图矩阵
uniform mat4 u_mvpMatrix;//模型视图透视矩阵
uniform mat3 u_Normal;// 模型视图矩阵的 rotation

uniform LightAttribute u_light;
uniform LightModeAttribute u_light_mode;
uniform LightMaterialAttribute u_light_material;


vec4 ads_dirction()
{
	vec4 result_color;
	// ambinet color
	result_color = u_light_material.m_m_emission + u_light_mode.m_model_ambient * u_light_material.m_m_ambient ;
					//+ u_light_mode.m_model_ambient * u_light_material.m_m_diffuse;

	// light dir
	vec3 eye_normal = vec3( normalize( u_mvMatrix * vec4( a_normal,0.0)) );
	vec4 eye_position4 = u_mvMatrix * a_position;
	vec4 light_position4 = u_mvMatrix * u_light.m_position;
	// vec3 eye_position3 = eye_position4.xyz / eye_position4.w;
	vec3 aux = vec3(eye_position4) - vec3( light_position4 );
	vec3 half_vector = normalize( vec3(u_light.m_position)  - aux ) ;
	vec3 light_dir = normalize( aux ); // 方向
	
	
	float spot_coscutoff = dot( normalize( u_light.m_spot_dirction ) , light_dir);
	vec4 diffuse = u_light.m_diffuse * u_light_material.m_m_diffuse;
	vec4 ambient = u_light.m_ambient * u_light_material.m_m_ambient;
	vec4 specular = u_light.m_specular * u_light_material.m_m_specular;
	
	if( spot_coscutoff  >= u_light.m_spot_coscutoff)
	{
		float diff = max( 0.0 , dot(eye_normal, -light_dir) );
		if( diff > 0)
		{
			float att = 1.0f ;
			float spot_effect = pow(spot_coscutoff,u_light.m_spot_exponent);
			if( u_light.m_position.w != 0){
				float dists = length(aux);//距离
				att = spot_effect / ( u_light.m_constant_attenuation + u_light.m_linear_attenuation * dists
					+ u_light.m_quadratic_attenuation * dists * dists) ;
			}
		
			//vec3 reflection_light_dir = reflect( -light_dir ,eye_normal );
			float eye_reflection_angle = max( 0.0 ,dot( eye_normal , half_vector ) );
			float fspec = pow( eye_reflection_angle , u_light_material.m_m_shininess );
		
			result_color += att * ( specular * fspec + diffuse * diff + ambient);
		}
	}
	
	return result_color;
}

out vec4 varyingFragColor;

void main()
{
	gl_Position = u_mvpMatrix * a_position;
	
	varyingFragColor = ads_dirction() ;
}
