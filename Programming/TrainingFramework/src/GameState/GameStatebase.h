#pragma once

#ifdef WIN32
	#include "utilities.h" 
#else
#include "../../Utilities/Math.h"
#endif
#include "GameStateMachine.h"


class GameStateBase
{
public:
	GameStateBase(void){}
	virtual ~GameStateBase(void){}

	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameStateMachine* game) = 0;
	virtual void HandleKeyEvents(GameStateMachine* game, GLint key, bool bIsPressed) = 0;
	virtual void HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed) = 0;
	virtual void Update(GameStateMachine* game, GLfloat deltaTime ) = 0;
	virtual void Draw(GameStateMachine* game) = 0;

	void ChangeState(GameStateMachine* game, GameStateBase* state) {
		game->ChangeState(state);
	}

	static GameStateBase* CreateState(StateTypes stt);
	

};

