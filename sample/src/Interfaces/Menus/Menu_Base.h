#ifndef __MENUBASE_H__
#define __MENUBASE_H__
#include <list>
#include "MenuMgr.h"
class SceneNode;
class Menu_Base
{
protected:
	SceneNode*			m_MenuInterface;
	std::string			m_name;
	MenuMgr::EMenuState m_MenuState;
	void LoadInterface();
public:
	Menu_Base();
	void SetState(MenuMgr::EMenuState state);
	MenuMgr::EMenuState GetState();
	std::string GetName();
	virtual ~Menu_Base();
	virtual void Init() {};
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void OnEnter(){};
	virtual void Refresh() {};	
	virtual void OnQuit(){};
	virtual void CleanUp();
	virtual void HandleEvents() {};
	virtual void HandleKeyEvents(int key, bool bIsPressed) {};
	virtual void HandleTouchEvents(int x, int y, bool bIsPressed) {};
	
};
#endif