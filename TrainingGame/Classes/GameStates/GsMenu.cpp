/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GsMenu.h"

GsMenu::GsMenu()
{

}


GsMenu::~GsMenu()
{

}


void GsMenu::initialize()
{
	auto node = ResourceMgr::getInstance()->loadUI("mainmenu.json");
	this->addChild(node, 0);

	auto layer_loading = node->getChildByName("menu_contaner");
	auto play_button = (MenuItemImage*)layer_loading->getChildByName("play_button");
	auto setting_button = (MenuItemImage*)layer_loading->getChildByName("setting_button");
	auto exit_button = (MenuItemImage*)layer_loading->getChildByName("exit_button");

	play_button->setCallback(CC_CALLBACK_1(GsMenu::playgame, this));
	setting_button->setCallback(CC_CALLBACK_1(GsMenu::setting, this));
	exit_button->setCallback(CC_CALLBACK_1(GsMenu::exitgame, this));

	SoundMgr::getInstance()->playBackgroundMusic("mainmenu_bg_sound.wav", true);
}

void GsMenu::exit()
{
	SoundMgr::getInstance()->stopBackgroundMusic(true);
}


void GsMenu::pause()
{
	SoundMgr::getInstance()->stopBackgroundMusic(false);
}

void GsMenu::resume()
{
	SoundMgr::getInstance()->playBackgroundMusic("mainmenu_bg_sound.wav", true);
}


bool GsMenu::onTouchBegan(Touch *touch, Event *event)
{
	return 0;
}

void GsMenu::onTouchMoved(Touch *touch, Event *event)
{

}


void GsMenu::onTouchEnded(Touch *touch, Event *event)
{

}


void GsMenu::onTouchCancelled(Touch *touch, Event *event)
{

}


void GsMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		GameStateMachine::getInstance()->popState();
}


void GsMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void GsMenu::update(float deltaTime)
{

}

void GsMenu::playgame(cocos2d::Ref * pSender)
{
	SoundMgr::getInstance()->playEffect("button_click.wav");
	GameStateMachine::getInstance()->changeState(StateTypes::STATE_PLAY);
}

void GsMenu::setting(cocos2d::Ref * pSender)
{
	SoundMgr::getInstance()->playEffect("button_click.wav");
	GameStateMachine::getInstance()->changeState(StateTypes::STATE_SETTING);
}

void GsMenu::exitgame(cocos2d::Ref * pSender)
{
	SoundMgr::getInstance()->playEffect("button_click.wav");
	Director::getInstance()->end();
}
