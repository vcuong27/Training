#pragma once
#include "baseobject.h"


class Sprite3D :
	public BaseObject
{

private:
	Matrix		m_WorldMat;
	Vector4		m_Color;
	Vector2		m_Vec2DPos;

public:
	Sprite3D();
	~Sprite3D();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

	void		SetColor(Vector4 color);
};

