#pragma once
#include "IGUIElement.h"

class GLProgram;
class Font;

typedef enum{
	WHILE = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	BLACK
} EColor;

class Text:
	public IGUIElement
{
public:

	/*typedef enum
	{
		ARIAL = 0,
		TIME_NEW_ROMAN
	} EFont;
	typedef enum
	{
		TEXT_REGULAR		= 0,
		TEXT_BOLD			= 1,
		TEXT_ITALIC			= 2,
		TEXT_BOLD_ITALIC	= 3
	} ETextType;

	typedef struct
	{
		std::string		mFont;	
		Text::ETextType	mType;
	} STextStyle;
	*/

public:
	Text( SceneNode* parent, std::string text, EColor color, Vector2 position, Vector2 scale);
	~Text();
//	void			Init(EFont efont, Text::ETextType type);
	void			draw();
	void			update(GLfloat deltaTime);
	void			setFont(Font* font);
	void			setText(std::string text);
private:
//	std::string			_font;
	std::string			_text;
	Vector4				_color;
	Font*				_font;

	/*GLuint				texId;
	GLuint				vboId;
	Text::STextStyle	_Style;*/
	Vector4				EnumToVector(EColor color);
	//std::string			EnumToString(EFont font);
};
