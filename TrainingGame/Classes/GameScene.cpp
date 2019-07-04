/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GameScene.h"
#include "GameStates\GameStateMachine.h"
#include "GameStates\GameStatebase.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameScene::init()
{
	GAME_LOG("GameScene::init");
	auto touchListener = EventListenerTouchOneByOne::create();
	auto keyBoardListener = EventListenerKeyboard::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	this->scheduleUpdate();

	ResourceMgr::getInstance()->setPath("");

	return true;
}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	return GameStateMachine::getInstance()->onTouchBegan(touch, event);
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	GameStateMachine::getInstance()->onTouchMoved(touch, event);
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
	GameStateMachine::getInstance()->onTouchEnded(touch, event);
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{
	GameStateMachine::getInstance()->onTouchCancelled(touch, event);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GameStateMachine::getInstance()->onKeyPressed(keyCode, event);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	GameStateMachine::getInstance()->onKeyReleased(keyCode, event);
}

void GameScene::update(float delta)
{
	if (GameStateMachine::getInstance()->NeedsToChangeState())
	{
		this->removeAllChildren();
		GameStateMachine::getInstance()->performStateChange();
		this->addChild(GameStateMachine::getInstance()->getCurrentState().get());
	}

	GameStateMachine::getInstance()->update(delta);
}

