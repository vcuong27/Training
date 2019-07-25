#include "Menu_Pause.h"
std::string Menu_Pause::k_menu_name = "Menu_Pause";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Pause::Menu_Pause()
{
	m_name = Menu_Pause::k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Pause::~Menu_Pause()
{
}
void Menu_Pause::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Pause::Draw()
{
}
void Menu_Pause::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Pause::OnEnter()
{
}
void Menu_Pause::Refresh()
{
}
void Menu_Pause::OnQuit()
{
}
void Menu_Pause::CleanUp()
{
}
void Menu_Pause::HandleEvents()
{
}
void Menu_Pause::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Pause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}