#pragma once
#include "core\Singleton.h"
#include<list>


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

public:
	GameStateMachine();
	~GameStateMachine();


public:

	void Cleanup();

	void ChangeState(GameStateBase* state);
	void ChangeState(StateTypes stt);
	void PushState(StateTypes stt);
	void PopState();

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

	inline bool		HasState()const
	{
		return states.size() > 0;
	}

private:

	std::list<GameStateBase*>	states;
	GameStateBase*	m_pActiveState;
	GameStateBase*	m_pNextState;
	bool m_running;	
	bool m_fullscreen;
};

