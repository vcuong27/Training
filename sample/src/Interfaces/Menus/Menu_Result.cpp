#include "Menu_Result.h"
std::string Menu_Result::k_menu_name = "Menu_Result";
////////////////////////////////////////////////////////////////////////////////////////
Menu_Result::Menu_Result()
{
	m_name = k_menu_name;
	m_name.append(".json");
	Init();
}
Menu_Result::~Menu_Result()
{
}
void Menu_Result::Init()
{
	Menu_Base::LoadInterface();
}
void Menu_Result::Draw()
{
	Menu_Base::Draw();
}
void Menu_Result::Update(float deltaTime)
{
	Menu_Base::Update(deltaTime);
}
void Menu_Result::OnEnter()
{
}
void Menu_Result::Refresh()
{
}
void Menu_Result::OnQuit()
{
}
void Menu_Result::CleanUp()
{
	Menu_Base::CleanUp();
}
void Menu_Result::HandleEvents()
{
}
void Menu_Result::HandleKeyEvents(int key, bool bIsPressed)
{
}
void Menu_Result::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}