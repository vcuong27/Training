#include "Object.h"
#include "GraphicHeaders.h"

Object::Object(): mMoving(false)
{
}

void Object::SetGoToPostion(const Vector2& vec)
{
	mGoToPos = vec;
}

void Object::SetPostion(const Vector2& vec)
{
	mPostion = vec;
	mAnimation->SetAllSpritePostion(vec);
}

void Object::SetScale(const Vector2& vec)
{
	mScale = vec;
	mAnimation->SetAllSpriteScale(mScale);
}

void Object::SetAngleRotate(float angle)
{
	mAngle = angle;
	mAnimation->SetAllSpriteAngle(angle);
}


void Object::SetObjectDistance(Vector2 vec)
{
	mRect = Vector2(vec.x * mScale.x, vec.y * mScale.y);
};

#define HOLD_POS 2.0f


void Object::SetMoving()
{
	mMoving = true;
	mGoToPos = mPostion;
}

void Object::update(float dt)
{
	mAnimation->update(dt);
}
void Object::draw()
{
	mAnimation->draw();
}