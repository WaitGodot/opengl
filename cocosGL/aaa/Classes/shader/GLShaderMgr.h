#ifndef _SHADERMANAGER_H
#define _SHADERMANAGER_H
#include <map>


namespace glShaderSpace {

	enum ShaderKey{
		_Postion_Key,
		_PointLight_Key,
		_AdsLight_key,
		_Lightning_key,
	};


	class GLShaderProgram;

	class GLShaderMgr
	{
		std::map<ShaderKey,GLShaderProgram*> m_programMap;
		static GLShaderMgr* sg_ShaderManager;
	public:
		GLShaderMgr();
		~GLShaderMgr();

		GLShaderProgram* getByKey(ShaderKey key);
		void addProgram(ShaderKey key,GLShaderProgram* program);

		void init();

		static GLShaderMgr* shareShaderManager();
	};

#define shareGLShaderManager() glShaderSpace::GLShaderMgr::shareShaderManager()

}



#endif