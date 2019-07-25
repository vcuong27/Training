#pragma once
#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>

class Model
{

public:
//type model
static const GLuint	MODEL_TYPE_NFG;

static	Model* 		createWithFiles	(const std::string& vsFile, GLuint type);
		bool		initWithFiles	(const std::string& vsFile, GLuint type);

		GLuint		GetVertexObject();
		GLuint		GetIndiceObject();
		GLuint		GetNumIndiceObject();

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
		GLuint		_iNumIndices;
		GLuint		_iVboID; 
		GLuint		_iIboID;
		std::string _name;
		GLuint		_id;

};
