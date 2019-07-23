#pragma once
#include "baseobject.h"


class GameObject :
	public BaseObject
{

private:
	Matrix		m_WorldMat;
	Vector4		m_Color;
	Vector2		m_Vec2DPos;

public:
	GameObject();
	~GameObject();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);
	Vector2		Get2DPosition();
	void		SetColor(Vector4 color);
};

