#include "GLLight.h"


using namespace std;

namespace glShaderSpace
{

	static const string sg_GLLightString[] = {
		".m_ambient",".m_diffuse",".m_specular",".m_position",".m_spot_dirction",
		".m_spot_exponent",".m_spot_coscutoff",".m_constant_attenuation",".m_linear_attenuation",".m_quadratic_attenuation"
	};

	static const string sg_GLLightModeString[] = {
		".m_model_ambient"
	};

	static const string sg_GLLightMaterialAttribute[] = {
		".m_m_ambient",".m_m_diffuse",".m_m_specular",".m_m_emission",".m_m_shininess"
	};

	void LightAttribute::initWithLight( GLint programId,const char* name )
	{
		m_light_name = name;

		for ( int i = 0 ; i < LIGHT_ATTRIBUTE_NUM ; i ++)
		{
			m_light_name+sg_GLLightString[i];
			m_att_arr[i] = glGetUniformLocation(programId, (m_light_name+sg_GLLightString[i]).c_str() );
		}
	}

	void LightAttribute::update()
	{
		glUniform4fv(m_att_arr[0],1,(const float*)&m_ambient);
		glUniform4fv(m_att_arr[1],1,(const float*)&m_diffuse);
		glUniform4fv(m_att_arr[2],1,(const float*)&m_specular);
		glUniform4fv(m_att_arr[3],1,(const float*)&m_position);
		glUniform3fv(m_att_arr[4],1,(const float*)&m_spot_dirction);
		glUniform1f(m_att_arr[5],m_spot_exponent);
		glUniform1f(m_att_arr[6],m_spot_coscutoff); // �ϴ�����ֵ
		glUniform1f(m_att_arr[7],m_constant_attenuation);
		glUniform1f(m_att_arr[8],m_linear_attenuation);
		glUniform1f(m_att_arr[9],m_quadratic_attenuation);
	}

	void LightAttribute::setSpotCutoff( float angle )
	{
		m_spot_cutoff = angle;
		m_spot_coscutoff = cosf( DEGREE(m_spot_cutoff) );
	}


	void LightModelAttribute::initWithModel( GLint programId,const char* name )
	{
		m_model_name = name;
		for ( int i = 0 ; i < MODEL_ATTRUBUTE_NUM ; i++)
		{
			m_att_arr[i] = glGetUniformLocation(programId , (m_model_name + sg_GLLightModeString[i]).c_str());
		}
	}

	void LightModelAttribute::update()
	{
		glUniform4fv(m_att_arr[0],1,(const float*)&m_model_ambient);
	}

	void LightMaterialAttribute::initWithMaterial( GLint programId,const char* name )
	{
		m_material_name = name;

		for (int i = 0 ; i < MATERIAL_ATTRUBUTE_NUM ; i++)
		{
			m_att_arr[i] = glGetUniformLocation(programId , (m_material_name + sg_GLLightMaterialAttribute[i]).c_str());
		}
	}

	void LightMaterialAttribute::update()
	{
		glUniform4fv(m_att_arr[0],1,(const float*)&m_m_ambient);
		glUniform4fv(m_att_arr[1],1,(const float*)&m_m_diffuse);
		glUniform4fv(m_att_arr[2],1,(const float*)&m_m_specular);
		glUniform4fv(m_att_arr[3],1,(const float*)&m_m_emission);
		glUniform1f(m_att_arr[4],m_m_shininess);
	}

	GLLight::GLLight()
	{

	}

	GLLight::~GLLight()
	{

	}


	LightAttribute* GLLight::getLightAtt()
	{
		return &m_light_attribute;
	}

	LightMaterialAttribute* GLLight::getLightMatrialAtt()
	{
		return &m_light_material_attribute;
	}

	LightModelAttribute* GLLight::getLightModelAtt()
	{
		return &m_light_model_attribute;
	}

	void GLLight::initLightModule( GLint programId,const char* lightName,const char* lightModelName,const char* materialName )
	{
		m_light_attribute.initWithLight(programId,lightName);
		m_light_model_attribute.initWithModel(programId,lightModelName);
		m_light_material_attribute.initWithMaterial(programId,materialName);
	}

	void GLLight::updateLight()
	{
		m_light_attribute.update();
		m_light_model_attribute.update();
		m_light_material_attribute.update();
	}

}