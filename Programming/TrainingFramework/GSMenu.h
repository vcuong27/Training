#pragma once
#include "gamestatebase.h"

class Camera;
class Button;
class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents(GameStateMachine* game);
	void HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed);
	void HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed);
	void Update(GameStateMachine* game, GLfloat deltaTime);
	void Draw(GameStateMachine* game);

private:
	Camera*				m_pCam;
	std::list<Button*>	m_listButton;

	bool				m_isLogin;
};

