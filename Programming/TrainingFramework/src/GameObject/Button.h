#pragma once
#include "baseobject.h"

class Texture;
class GameStateMachine;
class Button :
	public BaseObject
{

private:
	Matrix			m_WorldMat;
	std::string		m_Text;
	Vector2			m_Vec2DPos;
	Texture*		m_pTexture;
	GLint			m_iHeight;
	GLint			m_iWidth;
	void			(*pBtClick)(GameStateMachine* game);
	bool			m_isHandle;
public:
	Button(void);
	~Button(void);

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);
	void		HandleTouchEvents(GameStateMachine* game, GLint x, GLint y, bool bIsPressed);

	void		SetText(std::string text);
	std::string	GetText();
	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);
	Vector2		Get2DPosition();
	void		SetTexture(Texture* texture);
	void		SetOnClick(void	(*pBtClick)(GameStateMachine* game));
	void		SetSize(GLint width, GLint height);

	bool		IsHandle();
};

