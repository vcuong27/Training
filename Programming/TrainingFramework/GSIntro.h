#pragma once
#include "gamestatebase.h"

class Shaders;
class GSIntro :
	public GameStateBase
{
public:
	GSIntro();
	~GSIntro();

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

};

