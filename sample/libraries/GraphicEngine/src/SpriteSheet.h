#pragma once

#include "SceneNode.h"

class SpriteSheet: public SceneNode
{
public:
	SpriteSheet(SceneNode* parent, Vector2& size , Vector2& spriteSize);
	~SpriteSheet();

	//static SpriteSheet* createSpriteSheetWithFile(std::string fileName, Vector2& size);
	//void setSize(const Vector2& size);
	//void setSpriteSize(const Vector2& size);
	void draw();
	void update(float dt);
	void setLenghTime(float delay) {mDelay = delay / mCount;};
	void ResetSpriteSheet();
protected:
	Vector2 mSize;
	Vector2 mSpriteSize;
	int mCount;
	int mRow;
	int mCloumn;
	//int mCurrentRow;
	int mCurrentPos;
	//int mCurrentColumn;
	float mDelay;
	float mTimer;
	Vector2 mUV;
};