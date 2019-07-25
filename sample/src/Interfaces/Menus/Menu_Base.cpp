#include "Menu_Base.h"
#include "GraphicHeaders.h"
#include "ResourceManagers.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
Menu_Base::Menu_Base()
{

}
Menu_Base::~Menu_Base()
{

}
std::string Menu_Base::GetName()
{
	return m_name;
}
void Menu_Base:: Draw()
{
	m_MenuInterface->draw();
}
void Menu_Base::Update(float deltaTime)
{
	m_MenuInterface->update(deltaTime);
}
void Menu_Base::SetState(MenuMgr::EMenuState state)
{
	m_MenuState = state;
}
MenuMgr::EMenuState Menu_Base::GetState()
{
	return m_MenuState;
}
void Menu_Base::CleanUp()
{
	delete m_MenuInterface;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Menu_Base::LoadInterface()
{
	Vector2 screen = Config::getInstance()->getScreenSize();
	std::string path = FileUtils::getInstance()->getAbsolutePath("GUI/Menus/");
	path.append(m_name);
	m_MenuInterface = new SceneNode(NULL);
	FILE* pFile;
#ifdef WIN32
	fopen_s(&pFile, path.c_str(), "rb");
#elif OS_ANDROID
	fopen(path.c_str(), "rb");
#endif
	fclose(pFile);
	///TODO : load data from file xml or json
	Sprite * background = new Sprite(m_MenuInterface);
	background->setPosition(Vector2(screen.x / 2, screen.y / 2));
	background->setScale(Vector2(1.0f, 1.0f));
	background->setTexture(SMResource->GetTextureByKey("background_2"));
	background->setGLProgram(SMResource->GetProgramByKey("RectShader"));
	background->setModel(SMResource->GetModelByKey("Rect"));
	background->setName("background");
}