#pragma once
#include "BaseObject.h"

enum class EColor {
	WHILE = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	BLACK
} ;

class Font;

class Text : public BaseObject
{
public:
	Text(Shaders* sha, Font* font, std::string text, EColor color, Vector2 position, float size);
	~Text();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;


	void			setFont(Font* font);
	void			setText(std::string text);

private:
	std::string			m_text;
	Font* m_font;

	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	Vector2	m_scale;
	Vector4 EnumToVector(EColor color);

};
