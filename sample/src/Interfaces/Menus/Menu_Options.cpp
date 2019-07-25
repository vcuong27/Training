#include "Menu_Options.h"
std::string Menu_Options::k_menu_name = "Menu_Options";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Options::Menu_Options()
{
	m_name = k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Options::~Menu_Options()
{
}
void Menu_Options::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Options::Draw()
{
	Menu_Base::Draw();
}
void Menu_Options::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Options::OnEnter()
{
}
void Menu_Options::Refresh()
{
}
void Menu_Options::OnQuit()
{
}
void Menu_Options::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_Options::HandleEvents()
{
}
void Menu_Options::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Options::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}