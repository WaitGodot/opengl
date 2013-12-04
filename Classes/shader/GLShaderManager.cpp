#include "GLShaderManager.h"
#include "GLShaderProgram.h"
#include "_MacroConfig.h"
using namespace std;

namespace glShaderSpace
{

	GLShaderManager::GLShaderManager()
	{

	}


	GLShaderManager::~GLShaderManager()
	{
		for (map<ShaderKey,GLShaderProgram*>::iterator it = m_programMap.begin();
			it != m_programMap.end(); ++it)
		{
			DELETE_SAFE( it -> second);
		}
		m_programMap.clear();
	}

	GLShaderManager* GLShaderManager::sg_ShaderManager = 0;

	GLShaderManager* GLShaderManager::shareShaderManager()
	{
		if (!sg_ShaderManager)
		{
			sg_ShaderManager = new GLShaderManager();
			//sg_ShaderManager->init();
		}
		return sg_ShaderManager;
	}

	void GLShaderManager::init()
	{
		GLShaderProgram* program = GLShaderProgram::createByFile("shaders/position.vert","shaders/position.frag");
		if (program)
		{
			addProgram(_Postion_Key,program);
		}
	}


	GLShaderProgram* GLShaderManager::getByKey( ShaderKey key )
	{
		map<ShaderKey,GLShaderProgram*>::iterator it;
		it = m_programMap.find(key);
		return it == m_programMap.end() ? NULL : it->second;
	}

	void GLShaderManager::addProgram( ShaderKey key,GLShaderProgram* program )
	{
		_ASSERT(program!=NULL,"program is nil!");
		m_programMap.insert(make_pair(key,program));
	}


}