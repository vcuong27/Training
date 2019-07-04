/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GSPlay.h"
#include "GameScene.h"

#include "GamePlay\BoardManager.h"
#include "GamePlay\ScoreManager.h"

GsPlay::GsPlay()
{

}


GsPlay::~GsPlay()
{

}


void GsPlay::initialize()
{
	auto node = ResourceMgr::getInstance()->loadUI("play_theme.json");
	this->addChild(node, 0);

	BoardManager::getInstance()->Init(node);
	ScoreManager::getInstance()->Init(node);

	auto layer_loading = node->getChildByName("menu_contaner");
	auto back_button = (MenuItemImage*)layer_loading->getChildByName("pause_button");
	back_button->setCallback(CC_CALLBACK_1(GsPlay::pausegame, this));

	SoundMgr::getInstance()->playBackgroundMusic("play_game_sound.wav", true);

}


void GsPlay::exit()
{
	SoundMgr::getInstance()->stopBackgroundMusic(true);
	ScoreManager::freeInstance();
	BoardManager::freeInstance();
}

void GsPlay::update(float deltaTime)
{
	ScoreManager::getInstance()->update(deltaTime);
}

void GsPlay::pause()
{

}

void GsPlay::resume()
{

}


bool GsPlay::onTouchBegan(Touch *touch, Event *event)
{
	return 0;
}

void GsPlay::onTouchMoved(Touch *touch, Event *event)
{

}


void GsPlay::onTouchEnded(Touch *touch, Event *event)
{

}


void GsPlay::onTouchCancelled(Touch *touch, Event *event)
{

}


void GsPlay::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void GsPlay::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		GameStateMachine::getInstance()->popState();
}



void GsPlay::pausegame(cocos2d::Ref * pSender)
{
	SoundMgr::getInstance()->playEffect("button_click.wav");
	GameStateMachine::getInstance()->popState();
}
