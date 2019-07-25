#ifndef __RESOURCE_MANAGERS__
#define __RESOURCE_MANAGERS__
#include "core/Singleton.h"
#include <map>
#include <string>
//

class GLProgram;
class Texture;
class Model;

class ResourceManagers : public CSingleton<ResourceManagers>
{
public:
	ResourceManagers();
	~ResourceManagers();

	void InitResources(std::string filename);

	void AddGLProgram(std::string key, GLProgram* program);
	GLProgram* GetProgramByKey(std::string key);

	void AddTexture(std::string key, Texture* texture);
	Texture* GetTextureByKey(std::string key);

	void AddModel(std::string key, Model* model);
	Model* GetModelByKey(std::string key);
protected:
private:
	std::map<std::string, GLProgram*> m_mapProgram;
	typedef std::map<std::string, GLProgram*>::iterator ProgramIterator;

	std::map<std::string, Texture*> m_mapTextures;
	typedef std::map<std::string, Texture*>::iterator TexturesIterator;

	std::map<std::string, Model*> m_mapModel;
	typedef std::map<std::string, Model*>::iterator ModelIterator;
};

#endif //__RESOURCE_MANAGERS__