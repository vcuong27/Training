#include "Font.h"
#include "utils\FileUtils.h"

Font* Font::createWithFiles	(EFont efont, ETextType type)
{
	auto texture = new Font();

	if (texture && texture->initWithFiles(efont, type))
	{
		return texture;
	}

	delete texture;
	texture = 0;

	return nullptr;
}

bool Font::initWithFiles	(EFont efont, ETextType type)
{
	std::string FONT_PATH = "../data/Fonts/";
	std::string font = enumToString(efont);
	STextStyle _Style;
	_Style.mType = type;
	switch(type)
	{
	case TEXT_BOLD:
		font.append("bd");
		break;
	case TEXT_ITALIC:
		font.append("i");
		break;
	case TEXT_BOLD_ITALIC:
		font.append("bi");
		break;
	default :
		break;
	}
	font.append(".ttf");
	if(FT_Init_FreeType(&_library))
	{
		printf("Could not init freetype library\n");
		return false;
	}
	_Style.mFont = FONT_PATH.append(font);
	if(FT_New_Face(_library, _Style.mFont.c_str(), 0, &_face)) {
		printf("Could not open font arial.ttf\n");
		return false;
	}
	FT_Set_Pixel_Sizes(_face, 0, 48);
	_glyphSlot = _face->glyph;

	glGenTextures(1, &_iTextID);
	glBindTexture(GL_TEXTURE_2D, _iTextID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wapMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filterMode);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filterMode);

	if((filterMode== GL_LINEAR_MIPMAP_LINEAR)||(filterMode== GL_LINEAR_MIPMAP_NEAREST)|| (filterMode== GL_NEAREST_MIPMAP_LINEAR)||(filterMode== GL_NEAREST_MIPMAP_NEAREST))
	glGenerateMipmap(GL_TEXTURE_2D);
	*/
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &_vboId);
	return true;
}

std::string Font::enumToString(EFont font)
{
	std::string sfont = "";
	switch(font)
	{
	case ARIAL:
		sfont.append("arial");
		break;
	case TIME_NEW_ROMAN:
		sfont.append("times");
		break;
	}
	return sfont;
}

GLuint Font::getTextFontAdd()
{
	return _iTextID;
}

GLuint Font::getArrBuffer()
{
	return _vboId;
}

FT_Face Font::getFtFace(){
	return _face;
}

FT_GlyphSlot Font::getFtGlyph(){
	return _glyphSlot;
}