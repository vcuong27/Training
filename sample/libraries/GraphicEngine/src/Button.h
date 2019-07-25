#pragma once
#include "IGUIElement.h"

class Texture;
class Button :
	public IGUIElement
{

private:
	std::string		_Text;
	GLint			_iHeight;
	GLint			_iWidth;

public:
	Button(EGUI_ELEMENT_TYPE type,SceneNode* parent);

	~Button(void);

	void		draw();
	void		update(GLfloat deltatime);

	void		setText(std::string text);
	std::string	getText();
	void		setSize(GLint width, GLint height);
};

