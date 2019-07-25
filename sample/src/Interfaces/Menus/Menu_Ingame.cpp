#include "Menu_Ingame.h"
std::string Menu_Ingame::k_menu_name = "Menu_Ingame";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Ingame::Menu_Ingame()
{
	m_name = k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Ingame::~Menu_Ingame()
{
}
void Menu_Ingame::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Ingame::Draw()
{
	Menu_Base::Draw();
}
void Menu_Ingame::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Ingame::OnEnter()
{
}
void Menu_Ingame::Refresh()
{
}
void Menu_Ingame::OnQuit()
{
}
void Menu_Ingame::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_Ingame::HandleEvents()
{
}
void Menu_Ingame::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Ingame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}