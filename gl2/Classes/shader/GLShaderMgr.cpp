#include "GLShaderMgr.h"
#include "GLShaderProgram.h"
#include "MacroConfig.h"
#include "GLLight.h"
using namespace std;

namespace glShaderSpace
{

	GLShaderMgr::GLShaderMgr()
	{

	}


	GLShaderMgr::~GLShaderMgr()
	{
		for (map<ShaderKey,GLShaderProgram*>::iterator it = m_programMap.begin();
			it != m_programMap.end(); ++it)
		{
			DELETE_SAFE( it -> second);
		}
		m_programMap.clear();
	}

	GLShaderMgr* GLShaderMgr::sg_ShaderManager = 0;

	GLShaderMgr* GLShaderMgr::shareShaderManager()
	{
		if (!sg_ShaderManager)
		{
			sg_ShaderManager = new GLShaderMgr();
			//sg_ShaderManager->init();
		}
		return sg_ShaderManager;
	}

	void GLShaderMgr::init()
	{
		GLShaderProgram* program = GLShaderProgram::createByFile("shaders/position.vert","shaders/position.frag");
		if (program)
		{
			addProgram(_Postion_Key,program);
		}

		program = GLShaderProgram::createByFile("shaders/point_light.vert","shaders/point_light.frag");
		if (program)
		{
			GLLight* light = new GLLight();
			light->initLightModule(program->getProgram(),"u_light","u_light_mode","u_light_material");
			program->addGLLight(light);

			addProgram(_PointLight_Key,program);
		}
		                                                                                                                                                
		program = GLShaderProgram::createByFile("shaders/ads_light.vert","shaders/ads_light.frag");
		if (program)
		{
			GLLight* light = new GLLight();
			light->initLightModule(program->getProgram(),"u_light","u_light_mode","u_light_material");
			program->addGLLight(light);

			addProgram(_AdsLight_key,program);
		}

		program = GLShaderProgram::createByFile("shaders/lightning.vert","shaders/lightning.frag");
		if (program)
		{
			addProgram(_Lightning_key,program);
		}

		program = GLShaderProgram::createByFile("shaders/sprite.vert","shaders/sprite.frag");
		if (program)
		{
			addProgram(_Texture_key,program);
		}
	}


	GLShaderProgram* GLShaderMgr::getByKey( ShaderKey key )
	{
		map<ShaderKey,GLShaderProgram*>::iterator it;
		it = m_programMap.find(key);
		return it == m_programMap.end() ? NULL : it->second;
	}

	void GLShaderMgr::addProgram( ShaderKey key,GLShaderProgram* program )
	{
		_ASSERT(program!=NULL,"program is nil!");
		m_programMap.insert(make_pair(key,program));
	}


}