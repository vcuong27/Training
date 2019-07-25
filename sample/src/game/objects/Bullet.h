#ifndef __BULLET__
#define __BULLET__

#include "GraphicHeaders.h"
#include "Object.h"

class Person;

class Bullet: public Object
{
public:
	Bullet();
	~Bullet() {};
	void draw() ;
	void update(float dt);
	void setFired(bool iSet) {mFire = iSet;};
	void setBulletSpeed (float speed) {m_speed = speed;};
	void InitDefaultBullet();
	bool IsFried() {return mFire;};
	bool IsOnTarget() {return mOnTarget;};

	void SetOnTarget(Person*& person) {mOnTarget = true ; mPerson = person;};
private:
	bool mFire;
	bool mOnTarget;
	float m_speed;
	Person* mPerson;
	static float k_defaultSpeed;
};
#endif //__BULLET__