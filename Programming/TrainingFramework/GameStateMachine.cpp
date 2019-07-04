#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
{
	m_running		= true;
	m_pActiveState	= 0;
	m_pNextState	= 0;
}


GameStateMachine::~GameStateMachine()
{
}


void GameStateMachine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
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




void GameStateMachine::PushState(GameStateBase* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameStateMachine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Exit();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void GameStateMachine::HandleEvents() 
{
	// let the state handle events
	//states.back()->HandleEvents(this);
}

void GameStateMachine::HandleKeyEvents(GLint key, bool bIsPressed)
{
	states.back()->HandleKeyEvents(this, key , bIsPressed);
}

void GameStateMachine::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	states.back()->HandleTouchEvents(this, x, y, bIsPressed);
}

void GameStateMachine::Update(GLfloat deltaTime ) 
{
	// let the state update the game
	//states.back()->Update(this, deltaTime);
	if(m_pActiveState != 0)
		m_pActiveState->Update(this, deltaTime);
}

void GameStateMachine::Draw() 
{
	// let the state draw the screen
	//states.back()->Draw(this);
	if(m_pActiveState != 0)
		m_pActiveState->Draw(this);
}

void  GameStateMachine::PerformStateChange()
{
	if(m_pNextState	!= 0)
	{
		// cleanup the current state
		if ( !states.empty() ) {
			states.back()->Exit();
			delete states.back();
			states.pop_back();
		}

		// store and init the new state
		states.push_back(m_pNextState);
		states.back()->Init();
	}
	m_pActiveState	= m_pNextState;
	m_pNextState	= 0;

}