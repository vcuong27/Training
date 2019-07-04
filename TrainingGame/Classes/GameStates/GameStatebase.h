/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#ifndef __GAMESTATE_BASE_H__
#define __GAMESTATE_BASE_H__

#include "game_config.h"
#include "GameStateMachine.h"
#include "Managers\ResourceMgr.h"
#include "Managers\SoundMgr.h"

USING_NS_CC;

class GameStateBase : public Layer
{
public:
	GameStateBase(void){}
	virtual~GameStateBase(void){}

	virtual void initialize() = 0;
	virtual void exit() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;

	static std::shared_ptr<GameStateBase> CreateState(StateTypes stt);

	virtual bool onTouchBegan(Touch *touch, Event *event) = 0;
	virtual void onTouchMoved(Touch *touch, Event *event) = 0;
	virtual void onTouchEnded(Touch *touch, Event *event) = 0;
	virtual void onTouchCancelled(Touch *touch, Event *event) = 0;

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) = 0;
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) = 0;

	virtual void update(float deltaTime) = 0;

};

#endif // __GAMESTATE_BASE_H__
