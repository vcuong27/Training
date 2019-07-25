#include "Animation.h"

Animation::Animation(SceneNode* parent) : SceneNode(parent)
{

}

Animation::~Animation()
{
	//need delete all sprite sheets
}

void Animation::SetIdleAnimation()
{
	mCurrentState = STATE_IDLE;
	MapSpriteIterator it = mMapSprite.find(STATE_IDLE);
	if (it != mMapSprite.end())
	{
		mCurrentSprite = (*it).second;
	}
}

void Animation::AddSpriteAnimation(STATE state , SceneNode* sprite)
{
	mMapSprite.insert(std::pair<STATE,SceneNode*> (state, sprite));
}

void Animation::RunAnimation(STATE state)
{
	mCurrentState = state;
	MapSpriteIterator it = mMapSprite.find(state);
	if (it != mMapSprite.end())
	{
		mCurrentSprite = (*it).second;
	}
	else
	{
		mCurrentState = STATE_IDLE;
	}
}


void Animation::SetAllSpritePostion(Vector2 postion)
{
	for (MapSpriteIterator it = mMapSprite.begin(); it != mMapSprite.end(); it++)
	{
		(*it).second->setPosition(postion);
	}
}

void Animation::SetAllSpriteScale(Vector2 scale)
{
	for (MapSpriteIterator it = mMapSprite.begin(); it != mMapSprite.end(); it++)
	{
		(*it).second->setScale(scale);
	}
}

void Animation::SetAllSpriteAngle(float angle)
{
	for (MapSpriteIterator it = mMapSprite.begin(); it != mMapSprite.end(); it++)
	{
		(*it).second->setRotationByAngle(angle);
	}
}

void Animation::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mCurrentSprite)
		mCurrentSprite->draw();

	glDisable(GL_BLEND);
}
void Animation::update(float dt)
{
	if (mCurrentSprite)
		mCurrentSprite->update(dt);
}