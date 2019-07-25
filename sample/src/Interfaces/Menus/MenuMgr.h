#pragma once
#include <list>
#include <string>
#include "core/Singleton.h"
class Menu_Base;
class MenuMgr :
	public CSingleton <MenuMgr>
{
private:
	bool					m_extraMenusLoaded;
	std::list<Menu_Base*>	m_Menus;
	Menu_Base*				m_LastPlayMenu;
	void					AddNewMenu(Menu_Base* menu);
public:

	typedef enum
	{
		k_menuState_Unused = -1,
		k_menuState_Enter = 0,
		k_menuState_Play,
		k_menuState_Quit,
	} EMenuState;

	MenuMgr(void);
	~MenuMgr(void);
	void		Init();
	void		Update(float deltaTime);
	void		Draw();
	void		PushMenu(std::string name);
	void		PopMenu();
	void		CleanUp();
	Menu_Base*  GetMenu(std::string name);
	Menu_Base*	GetCurrentPlayingMenu();
	void		Loading_AddExtraMenus();
private:
	typedef std::list<Menu_Base*>::iterator	ListIterator;
};

