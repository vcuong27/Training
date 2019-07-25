#pragma once

#include "SceneNode.h"
#include "Math.h"
#include <list>
#include <string>

class GLProgram;
class Models;
class Camera;

enum EGUI_ELEMENT_TYPE
{
	//! A button (IGUIButton)
	EGUIET_BUTTON = 0,

	//! A static text (IGUIStaticText)
	EGUIET_STATIC_TEXT,

};

class IGUIElement : public SceneNode
{
public:
	IGUIElement(EGUI_ELEMENT_TYPE type,SceneNode* parent)
		:SceneNode(parent),
		_type(type)
	{
	};
	~IGUIElement()
	{
	}

	EGUI_ELEMENT_TYPE getType()
	{
		return _type;
	}

	
protected:
	EGUI_ELEMENT_TYPE	_type;
};

