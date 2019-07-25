#pragma once
#include "Math.h"
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H

typedef enum
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
	ETextType	mType;
} STextStyle;

class Font
{

public:

static	Font* createWithFiles	(EFont efont, ETextType type);
	bool		initWithFiles(EFont efont, ETextType type);
	GLuint		getTextFontAdd();
	GLuint		getArrBuffer();
	FT_Face		getFtFace();
	FT_GlyphSlot getFtGlyph();

	void setName(std::string name){
		_name	=	name;
	}
	std::string getName(){
		return _name;
	}
	void setId(GLuint id){
		_id		=	id;
	}
	GLuint getId(){
		return _id;
	}

private:
	std::string _name;
	GLuint		_id;
	GLuint		_vboId;
	GLuint		_iTextID;
	
	FT_Library			_library;
	FT_Face				_face;
	FT_GlyphSlot		_glyphSlot;

	std::string enumToString(EFont font);
};
