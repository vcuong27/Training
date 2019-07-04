/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#pragma once

#include "game_config.h"

class GameStateBase;

enum class StateTypes
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_LOADING,
	STATE_MENU,
	STATE_SETTING,
	STATE_PLAY,
};


class GameStateMachine : public CSingleton < GameStateMachine >
{
public:
	GameStateMachine();
	~GameStateMachine();

public:
	void pause();
	void resume();

	void cleanup();

	void changeState(StateTypes stt);
	void pushState(std::shared_ptr<GameStateBase>& state);
	void popState();

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onTouchCancelled(Touch *touch, Event *event);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float deltaTime);

	bool isRunning() { return m_running; }
	void quit() { m_running = false; }
	void performStateChange();

	inline std::shared_ptr<GameStateBase> getCurrentState()const
	{
		return m_pActiveState;
	}

	inline bool		NeedsToChangeState()const
	{
		return (m_pNextState != nullptr);
	}


private:

	std::list<std::shared_ptr<GameStateBase>> m_ListStates;
	std::shared_ptr<GameStateBase> m_pActiveState;
	std::shared_ptr<GameStateBase> m_pNextState;
	bool m_running;
	bool m_fullscreen;
	bool m_needCleanupState;
};

