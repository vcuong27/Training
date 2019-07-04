/****************************************************************************
Demo GameFramework
Created by Nguyen Van Cuong
Contact: cuongktpm@gmail.com
****************************************************************************/

#pragma once
#include "gamestatebase.h"

class GSIntro :
	public GameStateBase
{
public:
	GSIntro();
	~GSIntro();

	void initialize() override;
	void exit() override;
	void pause() override;
	void resume() override;

private:
	bool onTouchBegan(Touch *touch, Event *event) override;
	void onTouchMoved(Touch *touch, Event *event) override;
	void onTouchEnded(Touch *touch, Event *event) override;
	void onTouchCancelled(Touch *touch, Event *event) override;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

	void update(float deltaTime) override;
	float m_time;

};

