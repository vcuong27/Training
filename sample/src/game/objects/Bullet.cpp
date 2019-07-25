#include "Bullet.h"
#include "GameDefines.h"
#include "Person.h"
#include "GamePlay.h"

float Bullet::k_defaultSpeed = 500.0f;

Bullet::Bullet(): m_speed(k_defaultSpeed)
	, mFire(false)
	, mOnTarget(false)
{
	InitDefaultBullet();
}

void Bullet::InitDefaultBullet()
{
	Vector2 posCupid = GamePlay::GetInstance()->getPostionCupid();

	Sprite * cupid = new Sprite(nullptr);
	cupid->setTexture(SMResource->GetTextureByKey("arrow"));
	cupid->setGLProgram(SMResource->GetProgramByKey("RectShader"));
	cupid->setModel(SMResource->GetModelByKey("Rect"));
	mAnimation = new Animation(nullptr);
	mAnimation->AddSpriteAnimation(Animation::STATE_IDLE , cupid);
	SetPostion(Vector2(posCupid.x, posCupid.y)); 
	SetObjectDistance(Vector2(32 , 228)); //unhard code
	SetScale(Vector2(0.1f, 0.1f));
	mAnimation->SetIdleAnimation();
}

void Bullet::draw()
{
	mAnimation->draw();
}

void Bullet::update(float dt)
{
	//call new pos;
	//Vector2 currentPos = mPostion;
	if (mOnTarget)
	{
		//move same with target
		mAnimation->SetAllSpritePostion(mPerson->GetPostion());
	} else if (mFire)
	{
		//mPostion = vecVelocity * dt;
		Vector2 nextPos = mPostion + (vecVelocity * (k_defaultSpeed * dt));// , mPostion.y + (vecVelocity * dt) );
		mPostion = nextPos;
		mAnimation->SetAllSpritePostion(mPostion);
	}
	else
	{
		mAnimation->SetAllSpritePostion(GamePlay::GetInstance()->getPostionCupid());
	}

	Object::update(dt);
}