#ifndef _SHADERMANAGER_H
#define _SHADERMANAGER_H
#include <map>


namespace glShaderSpace {

	enum ShaderKey{
		_Postion_Key,

	};


	class GLShaderProgram;

	class GLShaderManager
	{
		std::map<ShaderKey,GLShaderProgram*> m_programMap;
		static GLShaderManager* sg_ShaderManager;
	public:
		GLShaderManager();
		~GLShaderManager();

		GLShaderProgram* getByKey(ShaderKey key);
		void addProgram(ShaderKey key,GLShaderProgram* program);

		void init();

		static GLShaderManager* shareShaderManager();
	};

#define shareGLShaderManager() GLShaderManager::shareShaderManager()

}



#endif