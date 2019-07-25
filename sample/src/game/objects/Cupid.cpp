#include "Cupid.h"
#include "GameDefines.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GSPlay.h"
std::string Cupid::k_name = "CUPID";

Cupid::Cupid():Object()
	, mMoving(false)
{
	mIsRunAnimation = false;
	mMoveSpeed = 200.0f;
	Init();
}

void Cupid::Init()
{
	Vector2 screen = Config::getInstance()->getScreenSize();
	mAnimation = new Animation(nullptr);

	Sprite * cupid = new Sprite(nullptr);
	cupid->setTexture(SMResource->GetTextureByKey("bow"));
	cupid->setGLProgram(SMResource->GetProgramByKey("RectShader"));
	cupid->setModel(SMResource->GetModelByKey("Rect"));
	//cupid->setPosition(Vector2(screen.x, screen.y));

	//cupid->setScale(Vector2(1.0f, 1.0f));
	mAnimation->AddSpriteAnimation(Animation::STATE_IDLE , cupid);
////
	SpriteSheet* spriteSheet = new SpriteSheet(nullptr, Vector2(436, 72), Vector2(109,72));
	spriteSheet->setTexture(SMResource->GetTextureByKey("cupid"));
	spriteSheet->setModel(SMResource->GetModelByKey("Rect"));
	spriteSheet->setGLProgram(SMResource->GetProgramByKey("SpriteShader"));
	spriteSheet->setLenghTime(0.13f);
	//spriteSheet->setPosition(Vector2(screen.x, screen.y));

	//spriteSheet->setScale(Vector2(1.0f, 1.0f));
	
	mAnimation->AddSpriteAnimation(Animation::STATE_RUN, spriteSheet);

	//mAnimation->setPosition(Vector2(screen.x / 2, screen.y / 2));
	//mAnimation->setScale(Vector2(1.0f, 1.0f));
	SetPostion(Vector2(screen.x / 2, 100 ));
	SetScale(Vector2(0.1f, 0.1f));
	//mAnimation->SetAllSpriteScale(Vector2(0.3f, 0.3f));

	//mAnimation->SetAllSpritePostion(Vector2(screen.x / 2, screen.y / 2));

	//need one for draw correctr
	mAnimation->SetIdleAnimation();

	SetName(Cupid::k_name);
	
}

Cupid::~Cupid()
{

}

#define HOLD_POS 2.0f

void Cupid::SetMoving()
{
	mMoving = true;
	mGoToPos = mPostion;
}

void Cupid::update(float dt)
{
	//call new pos;
	//Vector2 currentPos = mPostion;
	if (mMoving)
	{
		if (abs(mPostion.x - mGoToPos.x) > HOLD_POS || abs(mPostion.y - mGoToPos.y) > HOLD_POS)
		{
			//mPostion = vecVelocity * dt;
			Vector2 nextPos = mPostion + (vecVelocity * mMoveSpeed * dt);// , mPostion.y + (vecVelocity * dt) );
			mPostion = nextPos;
			mAnimation->SetAllSpritePostion(mPostion);
			(static_cast<GSPlay*>(GameStateMachine::GetInstance()->CurrentState()))->SetNewPostionForBullet();
		}
		else
		{
			mMoving = false;
		}
	}

	Object::update(dt);
}

void Cupid::StopAnimation()
{
	mAnimation->SetIdleAnimation();
	mIsRunAnimation = false;
}
