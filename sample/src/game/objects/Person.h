#pragma once
#include "Object.h"

class Person: public Object
{
public:
	Person();
	~Person();
	void update(float dt);

	void Init();
	void SetAnimation(Animation::STATE state) {mAnimation->RunAnimation(state);};

private:

};

