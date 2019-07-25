#include "Menu_Social.h"
std::string Menu_Social::k_menu_name = "Menu_Social";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Social::Menu_Social()
{
	m_name = k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Social::~Menu_Social()
{
}
void Menu_Social::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Social::Draw()
{
	Menu_Base::Draw();
}
void Menu_Social::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Social::OnEnter()
{
}
void Menu_Social::Refresh()
{
}
void Menu_Social::OnQuit()
{
}
void Menu_Social::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_Social::HandleEvents()
{
}
void Menu_Social::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Social::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}