#include "Button.h"
#include "Texture.h"
#include "Vertex.h"

extern GLint screenWidth;
extern GLint screenHeight;

Button::Button(EGUI_ELEMENT_TYPE type,SceneNode* parent) : IGUIElement (EGUI_ELEMENT_TYPE::EGUIET_BUTTON, parent)
{
	setScale(Vector2( 0.5, 0.15));
	setPosition(Vector2(-1,-1));
}


Button::~Button(void)
{
}

void Button::draw()
{

	SceneNode::draw();
}


void Button::setText(std::string text)
{
	_Text = text;
}

std::string Button::getText()
{
	return _Text;
}

void Button::setSize(GLint width, GLint height)
{
	_iWidth	= width;
	_iHeight	= height;
}
