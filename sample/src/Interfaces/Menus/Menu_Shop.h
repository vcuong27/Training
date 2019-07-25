#ifndef __MENU_SHOP__
#define __MENU_SHOP__
#include "Menu_Base.h"
class Menu_Shop :
	public Menu_Base
{
private:
public:
	static std::string k_menu_name;
	Menu_Shop();
	~Menu_Shop();
	void Init();
	void Draw();
	void Update(float deltaTime);
	void OnEnter();
	void Refresh();	
	void OnQuit();
	void CleanUp();
	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
};
#endif