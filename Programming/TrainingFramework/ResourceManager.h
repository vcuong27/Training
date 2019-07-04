#pragma once
#ifdef WIN32
	#include "../Utilities/utilities.h" 
#else
#include "../../Utilities/Math.h"
#include "Singleton.h"
#endif

class Models;
class Shaders;
class Texture;

class ResourceManager : public CSingleton<ResourceManager>
{
private:
	Models		**m_Models;
	Texture		**m_2DTextures;
	Shaders		**m_Shaders;
	GLuint		m_iNum2DTex;
	GLuint		m_iNumModel; 
	GLuint		m_iNumHeightMap; 
	GLuint		m_iNumShader;
public:
	ResourceManager();
	~ResourceManager();
	void		Init(const char *szFileName);
	Models*		GetModels(GLuint);
	Texture*	GetTexture(GLuint);
	Shaders*	GetShaders(GLuint);
};
