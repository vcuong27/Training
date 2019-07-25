#pragma once
#include "core/Singleton.h"
class Vector2;
class Rect;

class CollisionManagers: public CSingleton<CollisionManagers>
{
public:
	CollisionManagers();
	~CollisionManagers();
	void update(float dt);
	bool CheckBulletCollision(Vector2&, Rect&);
private:

};
