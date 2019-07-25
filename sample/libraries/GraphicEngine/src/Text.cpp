#include "Text.h"
#include "GLProgram.h"
#include "Font.h"
#include "Config.h"
#include "ft2build.h"
#include FT_FREETYPE_H

Text::Text( SceneNode* parent, std::string text, EColor color, Vector2 position, Vector2 scale)
	: IGUIElement(EGUI_ELEMENT_TYPE::EGUIET_STATIC_TEXT,parent)
{
	_text = text;
	_color = EnumToVector(color);
	setPosition(position);
	setScale(scale);

	char * vsFile = "Shaders/TextShaderVS.vs";
	char * fsFile = "Shaders/TextShaderFS.fs";
	//creation of shaders and program 
	_shaderProgram = GLProgram::createWithFiles(vsFile, fsFile);
}

Text::~Text()
{
}

Vector4 Text::EnumToVector(EColor color)
{
	Vector4 vecColor;
	switch(color)
	{
	case WHILE:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case RED:
		vecColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case GREEN:
		vecColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case BLUE:
		vecColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case YELLOW:
		vecColor = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case PURPLE:
		vecColor = Vector4(0.5f, 0.0f, 1.0f, 1.0f);
		break;
	case CYAN:
		vecColor = Vector4(0.0f, 0.9f, 0.9f, 1.0f);
		break;
	default :
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	return vecColor;
}
/*
std::string Text::EnumToString(EFont font)
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
*/
/*void Text::Init(EFont efont, Text::ETextType type)
{
	std::string FONT_PATH = "../data/Fonts/";
	std::string font = EnumToString(efont);
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
	if(FT_Init_FreeType(&library))
	{
		printf("Could not init freetype library\n");
		return;
	}
	_Style.mFont = FONT_PATH.append(font);
	if(FT_New_Face(library, _Style.mFont.c_str(), 0, &face)) {
		printf("Could not open font arial.ttf\n");
		return;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glyphSlot = face->glyph;

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, 0);


	glGenBuffers(1, &vboId);
}
*/

void Text::draw() {
	GLuint iTempShaderVaribleGLID = -1;

	_shaderProgram->use();

	glBindBuffer(GL_ARRAY_BUFFER, _font->getArrBuffer());


	iTempShaderVaribleGLID = _shaderProgram->getAttribute(GLProgram::ATTRIBUTE_POSITION);
	if(iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}


	iTempShaderVaribleGLID = _shaderProgram->getUniform((char*)"u_color");
	if(iTempShaderVaribleGLID !=-1)
		glUniform4fv(iTempShaderVaribleGLID,  1, &_color.x);

	iTempShaderVaribleGLID = _shaderProgram->getUniform((char*)"u_texture");
	if(iTempShaderVaribleGLID!= -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _font->getTextFontAdd());
		glUniform1i(iTempShaderVaribleGLID, 0);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float sx = 1.0f / Config::getInstance()->getScreenSize().x * _scale.x;
	float sy = 1.0f / Config::getInstance()->getScreenSize().y * _scale.y;
	float x = -1.0f + 2.0f *  _pos.x/Config::getInstance()->getScreenSize().x;
	float y = -1.0f + 2.0f * _pos.y/Config::getInstance()->getScreenSize().y;

	FT_GlyphSlot glyphSlot = _font->getFtGlyph();
	for(const char *p = _text.c_str(); *p; p++)
	{
		if(FT_Load_Char(_font->getFtFace(), *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyphSlot->bitmap.width,
			glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyphSlot->bitmap.buffer
			);
		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = -y - glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	SceneNode::draw();
}

void Text::update(GLfloat deltaTime) {
}

void Text::setFont(Font* font){
	_font = font;
}

void Text::setText(std::string text){
	_text = text;
}

