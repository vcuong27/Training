#include "CollisionManagers.h"
#include "GamePlay.h"
#include "objects/Bullet.h"
#include "objects/Person.h"
#include "GraphicHeaders.h"

CollisionManagers::CollisionManagers()
{
}

CollisionManagers::~CollisionManagers()
{
}

void CollisionManagers::update(float dt)
{
	GamePlay::PersonVector vecPerson = GamePlay::GetInstance()->GetAllPerson();
	GamePlay::BulletVector vecBullet = GamePlay::GetInstance()->GetAllBullet();
	//check bullet with person
	for (auto it: vecBullet)
	{
		if (it->IsFried() && !it->IsOnTarget())
		{
			//Rect rect1;
			float angle = it->GetAngleRotate();
			Vector2 pos = it->GetPostion();
			Vector2 posArrow = Vector2(pos.x , pos.y + it->GetObjectDistance().y / 2);
			if (angle != 0.0f)
			{
				Vector2 vecOther;
				vecOther.x = cos(angle) * (posArrow.x - pos.x) - sin(angle) * (posArrow.y - pos.y) + pos.x;
				vecOther.y = sin(angle) * (posArrow.x - pos.x) + cos(angle) * (posArrow.y - pos.y) + pos.y;
				posArrow = vecOther;
			}
			
			for (auto jt : vecPerson)
			{
				Rect rect2;
				rect2._pos = jt->GetPostion();
				rect2._distane = jt->GetObjectDistance();
				//check
				//if ()
				if (CheckBulletCollision(posArrow , rect2))
				{
					it->SetOnTarget(jt);
					GamePlay::GetInstance()->NeedSortAllList();
				}
				//set
			}
		}
	}

	//check person with person
	/*for (auto it : vecPerson)
	{
		if (CheckCollision)
	}*/
}

bool CollisionManagers::CheckBulletCollision(Vector2& posBullet , Rect& rec2)
{
	float rec2XN = rec2._pos.x - rec2._distane.x / 2;
	float rec2XP = rec2._pos.x + rec2._distane.x / 2;
	float rec2YN = rec2._pos.y - rec2._distane.y / 2;
	float rec2YP = rec2._pos.y + rec2._distane.y / 2;

	if ((posBullet.x > rec2XN && posBullet.x < rec2XP) && (posBullet.y > rec2YN && posBullet.y < rec2YP))
		return true;

	return false;
}