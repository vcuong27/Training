#pragma once

#include "SceneNode.h"
#include "esUtil.h"


class Sprite : public SceneNode
{
public:
	Sprite(SceneNode * parent);
	virtual ~Sprite();
	virtual void draw() override;
	virtual void update(float dt) override;

private:

};

