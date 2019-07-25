#ifndef __GAME_PLAY__
#define __GAME_PLAY__

#include <list>
#include "core\\Singleton.h"
#include "GraphicHeaders.h"

class Bullet;
class Cupid;
class Person;

class GamePlay: public CSingleton<GamePlay>
{
public:
	typedef std::vector <Person*> PersonVector;
	typedef std::vector <Bullet*> BulletVector;
	//enum direction
	enum DIRECTION
	{
		LEFT = 0,
		RIGHT,
		FORWARD,
		BACKWARD
	};

	GamePlay();
	~GamePlay();
	void update(float dt);
	void draw();
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void HandleKeyEvents(int keyCode, bool isPressed);
	void AddNewBullet(float angle);
	void AddNewPerson();
	void Move(DIRECTION direction);
	void NeedSortAllList() {mNeedSort = true;};

	void HandleBullet(int , int);
	void MoveSpeed(float move) {mMoveSpeed = move;};
	void ClearBulletOutScreen();
	void SetNewPostionForBullet();
	void ClearPersionOut();
	Vector2 getPostionCupid();

	PersonVector& GetAllPerson() {return mVectorPerson;};
	BulletVector& GetAllBullet() {return mVectorBullet;};

protected:
	//SceneNode* mCupid;
	Animation::STATE mRunState;
	bool mInited;
	SceneNode* mObjects;
	Cupid * mCupid;
	Person * mPerson;
	BulletVector mVectorBullet;
	typedef BulletVector::iterator VectorBulletIterator;

	PersonVector mVectorPerson;
	typedef PersonVector::iterator VectorPersonIterator;

	float mMoveSpeed;
private:
	int mBullet;
	bool mNeedSort;


};
#endif //__GAME_PLAY__