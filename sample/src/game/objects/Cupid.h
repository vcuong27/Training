#pragma once
#include "Object.h"

class Cupid : public Object
{
public:
	Cupid();
	~Cupid();
	//void draw();
	void update(float dt);
	void StopAnimation();
	void Init();
	void SetAnimation(Animation::STATE state) {mAnimation->RunAnimation(state);};
	void SetMoving();
private:
	bool mMoving;
};
