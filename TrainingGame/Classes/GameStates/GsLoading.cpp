/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#include "GsLoading.h"
#include "GameScene.h"

GsLoading::GsLoading()
{

}


GsLoading::~GsLoading()
{

}


void GsLoading::initialize()
{
	m_time = 0;

	auto node = ResourceMgr::getInstance()->loadUI("loading.json");
	this->addChild(node, 0);

	auto layer = node->getChildByName("layer_loading");
	auto loading_sprite = layer->getChildByName("loading_sprite");
	auto rotateTo = RotateBy::create(0.1f, 10.0f);
	loading_sprite->runAction(RepeatForever::create((Sequence*)Sequence::create(rotateTo, NULL)));

	SoundMgr::getInstance()->playBackgroundMusic("loading_screen.wav", true);
}

void GsLoading::exit()
{
	SoundMgr::getInstance()->stopBackgroundMusic(true);
}

void GsLoading::update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 3)
	{
		GameStateMachine::getInstance()->changeState(StateTypes::STATE_MENU);
		m_time = 0;
	}
}

void GsLoading::pause()
{

}

void GsLoading::resume()
{

}


bool GsLoading::onTouchBegan(Touch *touch, Event *event)
{
	return 0;
}

void GsLoading::onTouchMoved(Touch *touch, Event *event)
{

}


void GsLoading::onTouchEnded(Touch *touch, Event *event)
{

}


void GsLoading::onTouchCancelled(Touch *touch, Event *event)
{

}


void GsLoading::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}


void GsLoading::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		GameStateMachine::getInstance()->popState();
}

