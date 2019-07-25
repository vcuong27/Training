#ifndef __MENU_OPTIONS__
#define __MENU_OPTIONS__
#include "Menu_Base.h"
class Menu_Options :
	public Menu_Base
{
private:
public:
	static std::string k_menu_name;
	Menu_Options();
	~Menu_Options();
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