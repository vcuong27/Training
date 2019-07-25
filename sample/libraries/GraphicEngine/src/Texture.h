#pragma once
#include "Math.h"
#include <string>

class Texture
{

public:

static	Texture* createWithFiles	(const std::string& vsFile, GLuint wapMode = GL_REPEAT, GLuint filterMode = GL_LINEAR_MIPMAP_NEAREST);
	bool		initWithFiles(const std::string& vsFile, GLuint wapMode = GL_REPEAT, GLuint filterMode = GL_LINEAR_MIPMAP_NEAREST);
	GLuint		Get2DTextureAdd();

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
	GLuint		m_iTextGlId;
	GLuint		m_iTextID;
};
