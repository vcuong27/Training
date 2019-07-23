#pragma once
#include "baseobject.h"

class Sprite2D : public BaseObject
{

private:
	Matrix			m_WorldMat;
	std::string		m_Text;
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
public:
	Sprite2D();
	~Sprite2D();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

	void		SetText(std::string text);
	std::string	GetText();

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);
	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

};

