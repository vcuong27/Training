/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GameStateMachine.h"
#include "GameStateBase.h"


void GameStateMachine::pause()
{
	m_pActiveState->pause();
}

void GameStateMachine::resume()
{
	m_pActiveState->resume();
}

GameStateMachine::GameStateMachine()
{
	m_running		= true;
	m_pActiveState	= nullptr;
	m_pNextState	= nullptr;
	m_needCleanupState = false;
}


GameStateMachine::~GameStateMachine()
{
}


void GameStateMachine::cleanup()
{
	while ( !m_ListStates.empty() ) {
		m_ListStates.back()->exit();
		//delete m_ListStates.back();
		m_ListStates.pop_back();
	}
}

void GameStateMachine::changeState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gstb = GameStateBase::CreateState(stt);
	m_pNextState = gstb;
}

void GameStateMachine::pushState(std::shared_ptr<GameStateBase>& state)
{
	m_pNextState = state;
}

void GameStateMachine::popState()
{
	m_needCleanupState = true;
	m_ListStates.pop_back();
	if (m_ListStates.size() > 0)
		m_pNextState = m_ListStates.back();
	else
		m_running = false;
}

bool GameStateMachine::onTouchBegan(Touch *touch, Event *event)
{
	return m_pActiveState->onTouchBegan(touch, event);
}

void GameStateMachine::onTouchMoved(Touch *touch, Event *event)
{
	m_pActiveState->onTouchMoved(touch, event);
}

void GameStateMachine::onTouchEnded(Touch *touch, Event *event)
{
	m_pActiveState->onTouchEnded(touch, event);
}

void GameStateMachine::onTouchCancelled(Touch *touch, Event *event)
{
	m_pActiveState->onTouchCancelled(touch, event);
}

void GameStateMachine::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_pActiveState->onKeyPressed(keyCode, event);
}

void GameStateMachine::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	m_pActiveState->onKeyReleased(keyCode, event);
}

void GameStateMachine::update(float deltaTime ) 
{
	m_pActiveState->update(deltaTime);
}

void  GameStateMachine::performStateChange()
{
	if(m_pNextState	!= nullptr)
	{
		if (m_needCleanupState && !m_ListStates.empty() ) {
			m_pActiveState->exit();
			//m_pActiveState->release();
			m_needCleanupState = false;
		}
		else
		{
			m_ListStates.push_back(m_pNextState);
			m_pNextState->initialize();
		}
	}
	m_pActiveState	= m_pNextState;
	m_pNextState	= nullptr;

}