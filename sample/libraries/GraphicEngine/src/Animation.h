#pragma once

#include "SceneNode.h"
#include "SpriteSheet.h"

#include <map>

class Animation : public SceneNode
{
public:
	Animation(SceneNode* parent);
	~Animation();
	enum STATE
	{
		STATE_IDLE = 0,
		STATE_STAND,
		STATE_RUN,
		STATE_RUN_L,
		STATE_RUN_R,
		STATE_RUN_F,
		STATE_RUN_B,
		STATE_FLY,
		STATE_FRIE
	};

	void RunAnimation(STATE state);
	void SetIdleAnimation();
	void AddSpriteAnimation(STATE state , SceneNode* sprite);
	void SetAllSpritePostion(Vector2 postion);
	void SetAllSpriteScale(Vector2 scale);
	void SetAllSpriteAngle(float angle);

	void draw();
	void update(float dt);
protected:
	std::map<STATE, SceneNode*> mMapSprite;
	typedef std::map<STATE, SceneNode*>::iterator MapSpriteIterator;
	STATE mCurrentState;
	SceneNode* mCurrentSprite;
};
