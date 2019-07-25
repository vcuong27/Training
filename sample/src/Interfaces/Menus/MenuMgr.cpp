#include "MenuMgr.h"
#include "Menu_Base.h"
#include "Menu_MainMenu.h"
#include "Menu_Social.h"
#include "Menu_Options.h"
#include "Menu_Ingame.h"
#include "Menu_Pause.h"
#include "Menu_Result.h"
#include "Menu_Shop.h"

/////////////////////////////////////////////////////////////////////////////////////////////
MenuMgr::MenuMgr(void)
: m_extraMenusLoaded (false)
, m_LastPlayMenu (NULL)
{

}
/////////////////////////////////////////////////////////////////////////////////////////////
MenuMgr::~MenuMgr(void)
{

}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::CleanUp()
{
	for(ListIterator it = m_Menus.begin(); it != m_Menus.end(); it++)
	{
		(*it)->CleanUp();
		delete (*it);
	}
	m_Menus.clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::Init()
{
	Loading_AddExtraMenus();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::Update(float deltaTime)
{
	Menu_Base* curMenu = GetCurrentPlayingMenu();
	if(curMenu == NULL)
	{
		return;
	}
	curMenu->Update(deltaTime);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::Draw()
{
	Menu_Base* curMenu = GetCurrentPlayingMenu();
	if(curMenu == NULL)
	{
		return;
	}
	curMenu->Draw();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::PushMenu(std::string name)
{
	m_LastPlayMenu = GetCurrentPlayingMenu();
	if(m_LastPlayMenu)
	{
		m_LastPlayMenu->SetState(k_menuState_Quit);
		m_LastPlayMenu->OnQuit();
	}
	//Next menu to view
	Menu_Base* curMenu = GetMenu(name);
	curMenu->SetState(k_menuState_Enter);
	curMenu->OnEnter();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::PopMenu()
{
	Menu_Base* curMenu = GetCurrentPlayingMenu();
	if(curMenu)
	{
		curMenu->SetState(k_menuState_Quit);
		curMenu->OnQuit();
	}
	m_LastPlayMenu->SetState(k_menuState_Enter);
	m_LastPlayMenu->OnEnter();
	m_LastPlayMenu = curMenu;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::AddNewMenu(Menu_Base* menu)
{
	m_Menus.push_back(menu);
}
/////////////////////////////////////////////////////////////////////////////////////////////
Menu_Base* MenuMgr::GetMenu(std::string name)
{
	if(m_Menus.empty())
	{
		return NULL;
	}
	for(ListIterator it = m_Menus.begin(); it != m_Menus.end(); it++)
	{
		if( (*it)->GetName() == name)
		{
			return (*it);
		}
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////
Menu_Base* MenuMgr::GetCurrentPlayingMenu()
{
	if(m_Menus.empty())
	{
		return NULL;
	}
	for(ListIterator it = m_Menus.begin(); it != m_Menus.end(); it++)
	{
		if( ((*it)->GetState() == k_menuState_Enter)
			|| ((*it)->GetState() == k_menuState_Play))
		{
			return (*it);
		}
	}
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MenuMgr::Loading_AddExtraMenus()
{
	if(m_extraMenusLoaded)
	{
		return;
	}

	AddNewMenu( new Menu_MainMenu() );
	AddNewMenu( new Menu_Social() );
	AddNewMenu( new Menu_Options() );
	AddNewMenu( new Menu_Ingame() );
	AddNewMenu( new Menu_Pause() );
	AddNewMenu( new Menu_Result() );
	AddNewMenu( new Menu_Shop() );

	m_extraMenusLoaded = true;
}
/////////////////////////////////////////////////////////////////////////////////////////////