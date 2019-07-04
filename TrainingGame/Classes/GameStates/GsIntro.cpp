/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GsIntro.h"
#include "GameScene.h"

GSIntro::GSIntro()
{
	m_time = 0.0;
}


GSIntro::~GSIntro()
{

}


void GSIntro::initialize()
{
	auto node = ResourceMgr::getInstance()->loadUI("logo.json");
	this->addChild(node, 0);
}

void GSIntro::exit()
{

}

void GSIntro::update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.3)
	{
		GameStateMachine::getInstance()->changeState(StateTypes::STATE_LOADING);
		m_time = 0;
	}
}

void GSIntro::pause()
{

}

void GSIntro::resume()
{

}


bool GSIntro::onTouchBegan(Touch *touch, Event *event)
{
	return 0;
}

void GSIntro::onTouchMoved(Touch *touch, Event *event)
{

}


void GSIntro::onTouchEnded(Touch *touch, Event *event)
{

}


void GSIntro::onTouchCancelled(Touch *touch, Event *event)
{

}


void GSIntro::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void GSIntro::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

