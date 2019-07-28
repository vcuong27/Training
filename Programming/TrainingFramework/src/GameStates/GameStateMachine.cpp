
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
{
	m_running = true;
	m_pActiveState = 0;
	m_pNextState = 0;
}


GameStateMachine::~GameStateMachine()
{
}


void GameStateMachine::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Exit();
		delete states.back();
		states.pop_back();
	}
}

void GameStateMachine::ChangeState(StateTypes stt)
{
	GameStateBase* gstb = GameStateBase::CreateState(stt);
	ChangeState(gstb);
}

void GameStateMachine::ChangeState(GameStateBase* state)
{
	m_pNextState = state;
}


void GameStateMachine::PushState(StateTypes stt)
{
	GameStateBase* state = GameStateBase::CreateState(stt);
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	//states.push_back(state);
	//states.back()->Init();
	m_pNextState = state;
}

void GameStateMachine::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Exit();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

void  GameStateMachine::PerformStateChange()
{
	if (m_pNextState != 0)
	{
		// cleanup the current state
		if (!states.empty()) {
			states.back()->Exit();
			//delete states.back();
			states.pop_back();
		}

		// store and init the new state
		states.push_back(m_pNextState);
		states.back()->Init();
		m_pActiveState = m_pNextState;
	}

	m_pNextState = 0;
}