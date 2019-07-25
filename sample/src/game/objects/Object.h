#ifndef __OBJECT__
#define __OBJECT__

#include "GraphicHeaders.h"

class Object
{
public:
	Object();
	~Object() {};

	static std::string k_name;

	virtual void draw();
	virtual void update(float dt);
	
	void setVelocity( Vector2 vec) {
		vecVelocity = vec;
	};

	Vector2 getVelocity() {
		return vecVelocity;
	};

	void SetPostion(const Vector2& vec);// {mPostion = vec;};
	Vector2& GetPostion() {return mPostion;};

	void SetGoToPostion(const Vector2& vec);
	Vector2& GetGoToPostion() {return mGoToPos;};

	void SetAngleRotate(float angle);
	float GetAngleRotate() {return mAngle;};

	void SetScale(const Vector2& vec);// {mScale = vec;};
	Vector2& GetScale() {return mScale;};
	
	void SetMoveSpeed(float move) {mMoveSpeed = move;};
	void SetContainSize(const Vector2& vec) {containSize = vec;};

	std::string GetName(){return mName;};
	void SetName(const std::string& name ){mName = name;};

	void SetMoving();
	void SetObjectDistance(Vector2 vec) ;
	Vector2 GetObjectDistance() {return mRect;};

protected:
	Animation *mAnimation;

	Vector2 vecVelocity;
	Vector2 containSize;
	Vector2 mPostion;
	Vector2 mScale;
	Vector2 mGoToPos;
	Vector2 mRect;

	float mAngle;
	bool mMoving;
	bool mIsRunAnimation;
	float mMoveSpeed;
	std::string mName;
};
#endif //__OBJECT__