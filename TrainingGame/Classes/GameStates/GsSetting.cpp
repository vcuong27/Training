/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GsSetting.h"
#include "GameScene.h"


GsSetting::GsSetting()
{

}


GsSetting::~GsSetting()
{

}


void GsSetting::initialize()
{
	auto node = ResourceMgr::getInstance()->loadUI("setting.json");
	this->addChild(node, 0);

	auto layer_loading = node->getChildByName("menu_contaner");
	auto back_button = (MenuItemImage*)layer_loading->getChildByName("back_button");
	back_button->setCallback(CC_CALLBACK_1(GsSetting::backButton, this));

	SoundMgr::getInstance()->playBackgroundMusic("loading_screen.wav", true);
}


void GsSetting::exit()
{
	SoundMgr::getInstance()->stopBackgroundMusic(true);
}

void GsSetting::update(float deltaTime)
{

}

void GsSetting::pause()
{

}

void GsSetting::resume()
{

}


bool GsSetting::onTouchBegan(Touch *touch, Event *event)
{
	return 0;
}

void GsSetting::onTouchMoved(Touch *touch, Event *event)
{

}


void GsSetting::onTouchEnded(Touch *touch, Event *event)
{

}


void GsSetting::onTouchCancelled(Touch *touch, Event *event)
{

}


void GsSetting::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void GsSetting::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		GameStateMachine::getInstance()->popState();
}


void GsSetting::backButton(cocos2d::Ref * pSender)
{
	SoundMgr::getInstance()->playEffect("button_click.wav");
	GameStateMachine::getInstance()->popState();
}