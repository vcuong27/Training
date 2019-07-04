/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "game_config.h"

USING_NS_CC;

class GameScene : public Scene
{
public:
	bool init() override;
	static GameScene* create()
	{
		GameScene *ret = new (std::nothrow) GameScene();
		if (ret && ret->init())
		{
			ret->autorelease();
			return ret;
		}
		else
		{
			CC_SAFE_DELETE(ret);
			return nullptr;
		}
	}
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	virtual void onTouchCancelled(Touch *touch, Event *event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

//	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
//	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

	void update(float) override;

};

#endif // __GameScene_SCENE_H__
