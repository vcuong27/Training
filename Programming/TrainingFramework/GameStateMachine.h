#pragma once

#ifdef WIN32
#include "../Utilities/utilities.h" 
#else
#include "../../Utilities/Math.h"
#include "Singleton.h"
#include<list>
#endif

class GameStateBase;

enum StateTypes
{
	STATE_INVALID	= 0,
	STATE_Intro,
	STATE_Menu,
	STATE_Play,
};

class GameStateMachine : public CSingleton<GameStateMachine>
{

	//	__DeclareSingleton(GameStateMachine);

public:
	GameStateMachine();
	~GameStateMachine();


public:

	void Cleanup();

	void ChangeState(GameStateBase* state);
	void ChangeState(StateTypes stt);
	void PushState(GameStateBase* state);
	void PopState();

	void HandleEvents();
	void HandleKeyEvents(GLint key, bool bIsPressed);
	void HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void Update(GLfloat deltaTime );
	void Draw();

	bool isRunning() { return m_running; }
	void Quit() { m_running = false; }
	void PerformStateChange();

	inline GameStateBase*	CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool		NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}


private:

	std::list<GameStateBase*>	states;
	GameStateBase*	m_pActiveState;
	GameStateBase*	m_pNextState;
	bool m_running;	
	bool m_fullscreen;
};

