#include "ResourceManagers.h"
#include "GraphicHeaders.h"

ResourceManagers::ResourceManagers()
{


}

ResourceManagers::~ResourceManagers()
{

}


void ResourceManagers::InitResources(std::string filename)
{
	//TODO load from filename not use yet, 
	///juts hard code now
	char * modelFile = "Models/Bila.nfg";
	Model *model = Model::createWithFiles(modelFile, Model::MODEL_TYPE_NFG);
	AddModel("Bila" , model);

	Model *modelRect =  Model::createWithFiles("Models/Rect.nfg", Model::MODEL_TYPE_NFG);
	AddModel("Rect" , modelRect);

	char * vsFile = "Shaders/rect.vs";
	char * fsFile = "Shaders/rect.fs";
	//creation of shaders and program 
	GLProgram *program = GLProgram::createWithFiles(vsFile, fsFile);
	AddGLProgram("RectShader" , program);

	GLProgram *program1 = GLProgram::createWithFiles("Shaders/spriteShader.vs", "Shaders/spriteShader.fs");
	AddGLProgram("SpriteShader", program1);

	Texture *texure = Texture::createWithFiles("Textures/avatar_1.tga");
	AddTexture("Avatar1", texure);
	texure = Texture::createWithFiles("Textures/heart.tga");
	AddTexture("heart", texure);
	texure = Texture::createWithFiles("Textures/arrow.tga");
	AddTexture("arrow", texure);
	texure = Texture::createWithFiles("Textures/star.tga");
	AddTexture("star", texure);
	texure = Texture::createWithFiles("Textures/background.tga");
	AddTexture("background", texure);
	texure = Texture::createWithFiles("Textures/background_2.tga");
	AddTexture("background_2", texure);
	texure = Texture::createWithFiles("Textures/arrow_2.tga");
	AddTexture("arrow_2", texure);
	texure = Texture::createWithFiles("Textures/bow.tga");
	AddTexture("bow", texure);
	texure = Texture::createWithFiles("Textures/cupid.tga");
	AddTexture("cupid", texure);
}

void ResourceManagers::AddGLProgram(std::string key, GLProgram *program)
{
	m_mapProgram.insert(std::pair<std::string, GLProgram *>(key , program));
}

GLProgram* ResourceManagers::GetProgramByKey(std::string key)
{
	ProgramIterator _ptr = m_mapProgram.find(key);

	if (_ptr != m_mapProgram.end())
		return _ptr->second;

	return NULL;
}

void ResourceManagers::AddTexture(std::string key, Texture* texture)
{
	m_mapTextures.insert(std::pair<std::string, Texture *>(key , texture));
}
Texture* ResourceManagers::GetTextureByKey(std::string key)
{
	TexturesIterator _ptr = m_mapTextures.find(key);

	if (_ptr != m_mapTextures.end())
		return _ptr->second;

	return NULL;
}

void ResourceManagers::AddModel(std::string key, Model* model)
{
	m_mapModel.insert(std::pair<std::string, Model *>(key , model));
}

Model* ResourceManagers::GetModelByKey(std::string key)
{
	ModelIterator _ptr = m_mapModel.find(key);

	if (_ptr != m_mapModel.end())
		return _ptr->second;

	return NULL;
}