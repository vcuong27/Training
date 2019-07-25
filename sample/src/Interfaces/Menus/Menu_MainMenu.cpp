#include "Menu_MainMenu.h"
std::string Menu_MainMenu::k_menu_name = "Menu_MainMenu";
////////////////////////////////////////////////////////////////////////////////////////
Menu_MainMenu::Menu_MainMenu()
{
	m_name = Menu_MainMenu::k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_MainMenu::~Menu_MainMenu()
{
}
void Menu_MainMenu::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_MainMenu::Draw()
{
	Menu_Base::Draw();
}
void Menu_MainMenu::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_MainMenu::OnEnter()
{
}
void Menu_MainMenu::Refresh()
{
}
void Menu_MainMenu::OnQuit()
{
}
void Menu_MainMenu::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_MainMenu::HandleEvents()
{
	
}
void Menu_MainMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_MainMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}