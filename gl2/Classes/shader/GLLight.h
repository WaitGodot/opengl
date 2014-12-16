#ifndef _GL_LIGHT_H
#define _GL_LIGHT_H


#include "matrix/Vector3.h"
#include "matrix/Vector4.h"
#include <gl/glew.h>
#include <gl/GL.h>

using namespace cxMatrix;
#include <string>
#include <math.h>
#include "MacroConfig.h"

namespace glShaderSpace
{
	static const int LIGHT_ATTRIBUTE_NUM = 10;
	static const int MODEL_ATTRUBUTE_NUM = 1;
	static const int MATERIAL_ATTRUBUTE_NUM = 5;

	class LightAttribute
	{
	public:
		Vector4 m_ambient; //0
		Vector4 m_diffuse;//1
		Vector4 m_specular;//2
		Vector4 m_position;//3
		Vector3 m_spot_dirction;//4
		float   m_spot_exponent;//5
	private:
		float   m_spot_cutoff;float m_spot_coscutoff;//6
	public:
		float   m_constant_attenuation;//7
		float   m_linear_attenuation;//8
		float   m_quadratic_attenuation;//9

		std::string m_light_name;
		GLint m_att_arr[LIGHT_ATTRIBUTE_NUM];

		LightAttribute():
			m_ambient(0,0,0,1),
			m_diffuse(1,1,1,1),
			m_specular(1,1,1,1),
			m_position(0,0,1,0),
			m_spot_dirction(0,0,-1),
			m_spot_exponent(0),
			m_spot_cutoff(180),
			m_constant_attenuation(1),
			m_linear_attenuation(0),
			m_quadratic_attenuation(0),
			m_light_name("")
		{
			m_spot_coscutoff = cosf(DEGREE(180));
		}

		~LightAttribute()
		{

		}

		void setSpotCutoff(float angle);
		void initWithLight(GLint programId,const char* name);
		void update();
	};

	class LightModelAttribute
	{
	public:
		Vector4 m_model_ambient;

		std::string m_model_name;
		GLint m_att_arr[MODEL_ATTRUBUTE_NUM];

		LightModelAttribute():
			m_model_ambient(0.2,0.2,0.2,1.0)
		{

		}

		void initWithModel(GLint programId,const char* name);
		void update();
	};

	class LightMaterialAttribute
	{
	public:
		Vector4 m_m_ambient;
		Vector4 m_m_diffuse;
		Vector4 m_m_specular;
		Vector4 m_m_emission;
		float   m_m_shininess;
		
		std::string m_material_name;
		GLint m_att_arr[MATERIAL_ATTRUBUTE_NUM];

		LightMaterialAttribute():
			m_m_ambient(0.2,0.2,0.2,1),
			m_m_diffuse(0.8,0.8,0.8,1),
			m_m_specular(0,0,0,1),
			m_m_emission(0,0,0,1),
			m_m_shininess(0)
		{

		}

		void initWithMaterial(GLint programId,const char* name);
		void update();
	};

	class GLLight
	{
		LightAttribute m_light_attribute;
		LightMaterialAttribute m_light_material_attribute;
		LightModelAttribute m_light_model_attribute;

	public:
		GLLight();
		~GLLight();

		LightAttribute* getLightAtt();
		LightMaterialAttribute* getLightMatrialAtt();
		LightModelAttribute* getLightModelAtt();
		//
		void initLightModule(GLint programId,const char* lightName,const char* lightModelName,const char* materialName );
		void updateLight();
	};
}



#endif