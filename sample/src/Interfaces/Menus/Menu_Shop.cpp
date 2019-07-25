#include "Menu_Shop.h"
std::string Menu_Shop::k_menu_name = "Menu_Shop";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Shop::Menu_Shop()
{
	m_name = k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Shop::~Menu_Shop()
{
}
void Menu_Shop::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Shop::Draw()
{
	Menu_Base::Draw();
}
void Menu_Shop::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Shop::OnEnter()
{
}
void Menu_Shop::Refresh()
{
}
void Menu_Shop::OnQuit()
{
}
void Menu_Shop::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_Shop::HandleEvents()
{
}
void Menu_Shop::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Shop::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}