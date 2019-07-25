#ifndef __MENU_PAUSE__
#define __MENU_PAUSE__
#include "Menu_Base.h"
class Menu_Pause :
	public Menu_Base
{
private:
public:
	static std::string k_menu_name;
	Menu_Pause();
	~Menu_Pause();
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