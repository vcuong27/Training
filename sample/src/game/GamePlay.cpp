#include "GamePlay.h"
#include <time.h>
#include "SceneManagers.h"
#include "ResourceManagers.h"
#include "GraphicHeaders.h"

#include "objects\Bullet.h"
#include "GameDefines.h"
#include "objects/Cupid.h"
#include "objects/Person.h"

GamePlay::GamePlay() 
: mBullet(1)
, mInited(false)
, mMoveSpeed(50.0f)
{
	srand ( time(NULL) );
	Vector2 screen = Config::getInstance()->getScreenSize();

	//mObjects = new SceneNode(NULL);
	
	mCupid = new Cupid();
	mPerson = new Person();
	SMScene->AddGameObjectToScene(mCupid);
	AddNewBullet(0.0f) ;
	mInited = true;
}

void GamePlay::update(float dt)
{
	if( mVectorPerson.size() <= 5)
	{
		int x = rand()% (int)(500);
		if( x <= 3)
			AddNewPerson();
	}

	Vector2 screen = Config::getInstance()->getScreenSize();
	//mObjects->update(dt);
	
	mCupid->update(dt);
	for(auto it : mVectorPerson)
	{
		it->update(dt);
	}

	for(auto it : mVectorBullet)
	{
		it->update(dt);
	}

	ClearBulletOutScreen();
	ClearPersionOut();
}

void GamePlay::AddNewBullet(float angle) 
{
	mBullet++;
	Bullet* bullet = new Bullet();
	bullet->SetAngleRotate(angle);
	mVectorBullet.push_back(bullet);
}

void GamePlay::AddNewPerson()
{
	Vector2 screen = Config::getInstance()->getScreenSize();
	int x = rand()% (int)(10);
	Person* person = new Person();
	person->SetPostion(Vector2((screen.x / 10) * x + 70, screen.y - 77));
	person->setVelocity(Vector2(0,-1));
	mVectorPerson.push_back(person);
}

void GamePlay::HandleBullet(int x, int y)
{
	Vector2 pos(x ,y);
	Vector2 posCupid = getPostionCupid();
	Vector2 veclocity = pos - posCupid;
	//mCupid->SetAnimation(Animation::STATE_RUN);
	Bullet *bullet = mVectorBullet.back();
	veclocity.Normalize();
	bullet->setVelocity(veclocity);

	Vector2 vecy ( 0.0f , 1.0f);
	float angle = acosf(vecy.Dot(veclocity) / (veclocity.Length() * vecy.Length()));

	if (posCupid.x < pos.x)
	{
		angle = -angle;
	}
	bullet->SetAngleRotate(angle);
	//bulet->setFired(true);
	bullet->setFired(true);
	AddNewBullet(angle);
}
void GamePlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!bIsPressed)
	{
		HandleBullet(x, y);
	}
}

void GamePlay::ClearBulletOutScreen()
{
	//clear on list bullet
	VectorBulletIterator it = mVectorBullet.begin();
	while (it != mVectorBullet.end())
	{
		//check out screen
		bool neadMoveUp = true;
		if ((*it)->IsFried() && !(*it)->IsOnTarget())
		{
			Vector2 pos = (*it)->GetPostion();
			Vector2 screen = Config::getInstance()->getScreenSize();
			if (pos.x < 0 || pos.y < 0 || pos.x > screen.x || pos.y > screen.y)
			{
				auto bullet = *it;
				delete bullet;
				mVectorBullet.erase(it);
				it = mVectorBullet.begin(); //search again // @@ hard code 
			}
		}
		it++;
	}
}

void GamePlay::ClearPersionOut()
{
	//clear on list bullet
	VectorPersonIterator it = mVectorPerson.begin();
	while (it != mVectorPerson.end())
	{
		//check out screen

		Vector2 pos = (*it)->GetPostion();
		Vector2 screen = Config::getInstance()->getScreenSize();
		if (pos.x < 0 || pos.y < 0 || pos.x > screen.x || pos.y > screen.y)
		{
			auto bullet = *it;
			delete bullet;
			mVectorPerson.erase(it);
			//AddNewPerson();
			it = mVectorPerson.begin(); //search again // @@ hard code 
		}
		else
			it++;
	}
}

void GamePlay::HandleKeyEvents(int keyCode, bool isPressed)
{
	switch (keyCode)
	{
		case 'W':
			Move(FORWARD);
		break;
		case 'S':
			Move(BACKWARD);
		break;
		case 'A':
			Move(LEFT);
		break;
		case 'D':
			Move(RIGHT);
		break;
	}
}

void GamePlay::Move(DIRECTION direction)
{
	Vector2 currentPos;
	switch (direction)
	{

	case FORWARD:

		//setVelocity();
		currentPos = mCupid->GetPostion();
		mCupid->SetMoving();
		mCupid->SetGoToPostion(Vector2(currentPos.x , currentPos.y + mMoveSpeed));

		//calc velocity
		mCupid->setVelocity((mCupid->GetGoToPostion() - currentPos).Normalize());
		mRunState = Animation::STATE_RUN_F;
		break;
		
	case BACKWARD:
		currentPos = mCupid->GetPostion();
		mCupid->SetMoving();
		mCupid->SetGoToPostion(Vector2(currentPos.x , currentPos.y - mMoveSpeed));

		mCupid->setVelocity((mCupid->GetGoToPostion() - currentPos).Normalize());
		mRunState = Animation::STATE_RUN_B;
		break;
		
	case LEFT:
		currentPos = mCupid->GetPostion();
		mCupid->SetMoving();
		mCupid->SetGoToPostion(Vector2(currentPos.x  -  mMoveSpeed, currentPos.y));

		mCupid->setVelocity((mCupid->GetGoToPostion() - currentPos).Normalize());
		mRunState = Animation::STATE_RUN_L;
		break;
		
	case RIGHT:
		currentPos = mCupid->GetPostion();
		mCupid->SetMoving();
		mCupid->SetGoToPostion(Vector2(currentPos.x  +  mMoveSpeed , currentPos.y));

		mCupid->setVelocity((mCupid->GetGoToPostion() - currentPos).Normalize());
		mRunState = Animation::STATE_RUN_R;
		break;
	}
}
void GamePlay::draw()
{
	//mObjects->draw();

	for(auto it : mVectorPerson)
	{
		it->draw();
	}

	for(auto it : mVectorBullet)
	{
		it->draw();
	}
	
	mCupid->draw();

}
GamePlay::~GamePlay() 
{
	//wwo 
}

void GamePlay::SetNewPostionForBullet()
{
	for (auto it : mVectorBullet)
	{
		if (!it->IsFried())
		{
			it->SetPostion(getPostionCupid());
		}
	}
}

Vector2 GamePlay::getPostionCupid()
{
	return mCupid->GetPostion();
}
