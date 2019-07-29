#include "ResourceManagers.h"
#include "GameObject/Shaders.h"
#include "GameObject/Texture.h"
#include "GameObject/Models.h"
#include "GameObject/Camera.h"
#include "GameObject/Font.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/Sprite3D.h"
#include "GameObject/Text.h"


ResourceManagers::ResourceManagers()
{
	m_ShaderPath = "..\\Data\\Shaders\\";
	m_TexturePath = "..\\Data\\Textures\\";
}

ResourceManagers::~ResourceManagers()
{
}

void ResourceManagers::AddShader(const std::string& name)
{

}

void ResourceManagers::AddModel(const std::string& name)
{
}

void ResourceManagers::AddTexture(const std::string& name)
{
}

void ResourceManagers::AddFont(const std::string& name)
{
}

void ResourceManagers::RemoveShader(const std::string& name)
{
}

void ResourceManagers::RemoveModel(const std::string& name)
{
}

void ResourceManagers::RemoveTexture(const std::string& name)
{
}

void ResourceManagers::RemoveFont(const std::string& name)
{
}

std::shared_ptr<Shaders> ResourceManagers::GetShader(const std::string& name)
{
	auto it = m_MapShader.find(name);
	if (it != m_MapShader.end())
	{
		return it->second;
	}

	std::shared_ptr<Shaders>  m_Shaders;
	m_Shaders = std::make_shared<Shaders>();
	std::string vs = m_ShaderPath + name + ".vs";
	std::string fs = m_ShaderPath + name + ".fs";

	m_Shaders->Init(vs, fs);

	m_MapShader.insert(std::pair<std::string, std::shared_ptr<Shaders>>(name, m_Shaders));

	return m_Shaders;
}

std::shared_ptr<Texture> ResourceManagers::GetTexture(const std::string& name)
{
	auto it = m_MapTexture.find(name);
	if (it != m_MapTexture.end())
	{
		return it->second;
	}
	std::shared_ptr<Texture> m_texture = std::make_shared<Texture>();
	std::string file = m_TexturePath + name + ".tga";
	m_texture->Init(file.c_str(), GL_CLAMP_TO_EDGE, GL_LINEAR_MIPMAP_LINEAR);
	m_MapTexture.insert(std::pair<std::string, std::shared_ptr<Texture>>(name, m_texture));
	return m_texture;
}

std::shared_ptr<Models> ResourceManagers::GetModel(const std::string& name)
{
	std::shared_ptr<Models> m_model;
	m_model = std::make_shared<Models>("..\\Data\\Model\\Sprite2D.nfg", NFG);
	return m_model;
}

std::shared_ptr<Font> ResourceManagers::GetFont(const std::string& name)
{
	std::shared_ptr<Font> font = std::make_shared<Font>("..\\Data\\fonts\\arial.ttf");
	return font;
}
